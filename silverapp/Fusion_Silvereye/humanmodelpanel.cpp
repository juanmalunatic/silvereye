#include "humanmodelpanel.h"

#include "ogre3d_userlib/qtogrewindow.h"
#include "ogre3d_userlib/OgreGrid.h"
//#include "ogre3d_userlib/OgreGpuCommandBufferFlush.h"


#include <QDebug>
#include <QMainWindow>


#define EIGEN_DONT_ALIGN_STATICALLY
#include <Eigen/Geometry>

#include "mainwindow.h"

HumanModelPanel::HumanModelPanel(QWidget *parent) :

	QTOgreWindow( qobject_cast<QWindow *>(parent) )

{

	this->installEventFilter(this);

	// Members init

	mQisb = Ogre::Quaternion( Ogre::Degree(90) , Ogre::Vector3::UNIT_X );

	mBonePtrs.resize(7);
	mDerivedOrientations.resize(7);
	mAxesNodePtrs.resize(7);

	mSegmentQuats.resize(7);
	mJointQuats.resize(7);

}


HumanModelPanel::~HumanModelPanel()
{

	// Destruction of ogre scene handled in qtogrewindow.cpp
	qDebug() << "-------------- destructor humanmodelpanel--------------------- ";

}


/*
-----------------------------------------------------------------------
For the rendering to work, OgreWindow must be hidden instead of closed

As hiding is done with the X button and closeEvent is not avaliable for
QWindow, we must use an event filter.

[REFS]
http://stackoverflow.com/questions/21642943/qt-detect-when-qwindow-is-closed
http://www.informit.com/articles/article.aspx?p=1405544&seqNum=2
http://danostrov.com/2013/03/05/remove-your-qapplication-eventfilters/
-----------------------------------------------------------------------
*/

bool HumanModelPanel::eventFilter(QObject *obj, QEvent *event)
{
	 if ( event->type() == QEvent::Close )
	 {
		this->hide();
		QObject::disconnect(mConnectionToMainWindow);
		return true; // true stops the event

	 }

	 // copied from qtogrewindow.cpp
	 // (because we never instantiate it, hence no filter is setup)

	 if (obj == this)
	 {
		 if (event->type() == QEvent::Resize)
		 {
			 if (isExposed() && m_ogreWindow != NULL)
			 {
				 m_ogreWindow->resize(this->width(), this->height());
			 }
		 }
	 }

	 return QObject::eventFilter(obj, event);
}


// Handle connection to main window

void HumanModelPanel::setConnectionToMainWindow(const QMetaObject::Connection& connection)
{

	this->mConnectionToMainWindow = connection;

}



void HumanModelPanel::createScene()
{
	qDebug() << "-----------------crea escena------------------------";

	// Shadows (must be set up before entities)

	/*
	m_ogreSceneMgr->setShadowFarDistance(20.0);
	m_ogreSceneMgr->setShadowTextureSize(5120);
	m_ogreSceneMgr->setShowDebugShadows(true);
	*/

	//m_ogreSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE ); // <-- max performance

	m_ogreSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE );   // <-- nice looks (use me)


	/// LOG

	// Handled in qtogrewindow (edited the original file).
	//mBufferFlush.start(10); // call it regularly

	/// Window

	this->setHeight(600);
	this->setWidth (400);

						 //w  h
	m_ogreWindow->resize(400,600); // OpenGL needs this

	m_cameraMan->setTopSpeed(2);  // Camera speed.

	//m_ogreSceneMgr->showBoundingBoxes(true);

	/// Viewport

	Ogre::Viewport *viewport = m_ogreWindow->getViewport(0);
	viewport->setBackgroundColour( Ogre::ColourValue( 0.0f, 0.4f ,0.6f ) );

	/// Camera

	//DBG
	//http://www.ogre3d.org/forums/viewtopic.php?p=243226
	m_ogreCamera->setProjectionType( Ogre::PT_ORTHOGRAPHIC );
	m_ogreCamera->setOrthoWindow( 1 , 1.5 ); // leaving this here to remember proportions

	m_ogreCamera->setPosition( Ogre::Vector3(1.0f, -0.0f, 0.8f) );
	// For the orthographic camera, the first component of the position vector
	// represents a fraction of the total view. Resize the viewport instead,
	// to achieve http://www.ogre3d.org/forums/viewtopic.php?p=243226

	double fieldOfView = 1.5;
	m_ogreCamera->setOrthoWindow( fieldOfView , fieldOfView*1.5f );


	m_ogreCamera->setOrientation( Ogre::Quaternion(1,0,0,0) );
	m_ogreCamera->rotate( Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_Y) );
	m_ogreCamera->rotate( Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_X) );

	m_ogreCamera->setNearClipDistance(0.1f);
	m_ogreCamera->setFarClipDistance(200.0f);

	//DBG
	/*
	m_ogreCamera->rotate( Ogre::Quaternion(Ogre::Degree(-15), Ogre::Vector3::UNIT_Y) );
	m_ogreCamera->rotate( Ogre::Quaternion(Ogre::Degree(15), Ogre::Vector3::UNIT_Z) );
	*/

	/// Light

	m_ogreSceneMgr->setAmbientLight( Ogre::ColourValue(0.5,0.5,0.5) );

	Ogre::Light* light = m_ogreSceneMgr->createLight("MainLight");

	// NORMAL LIGHT

	//light->setPosition(20.0f, 0, 10.0f);   // ori
	//light->setType(Ogre::Light::LT_POINT); //ori

	// DEBUG LIGHT

	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(-1,0,0);

	/// Grid settings

	OgreGrid * grid = new OgreGrid(m_ogreSceneMgr, "BaseWhiteAlphaBlended"); // BaseWhiteAlphaBlended for transparency
	grid->attachToNode(m_ogreSceneMgr->getRootSceneNode());                  //Attach it to some SceneNode

	grid->setCellSize(1); // 1 ogre : 1 meter,

	grid->setDivisions(10);

	grid->xmin = -1;
	grid->ymin = -1;
	grid->ymax =  1;
	grid->xmax =  1;

	grid->showXY = true;  // XY is floor
	grid->showXZ = false;
	grid->showYZ = false;

	grid->colorDivision = Ogre::ColourValue(1.0f,1.0f,1.0f,0.3f);
	grid->colorOffset   = Ogre::ColourValue(1.0f,1.0f,1.0f,0.3f);
	grid->colorMaster   = Ogre::ColourValue(1.0f,1.0f,1.0f,0.3f);

	grid->update(); //Generate the grid

	/// Entities

	// WORLD AXES

	Ogre::Entity*    axesEntity    = m_ogreSceneMgr->createEntity("Axes.mesh");
	Ogre::SceneNode* axesSceneNode = m_ogreSceneMgr->getRootSceneNode()->createChildSceneNode();
	axesSceneNode->attachObject( axesEntity );
	axesSceneNode->setScale( 0.3f, 0.3f , 0.3f );

	Ogre::AxisAlignedBox axesBox = axesEntity->getWorldBoundingBox(true);

	// HUMAN

	mpHumanEntity  = m_ogreSceneMgr->createEntity("humano.mesh");
	mpHumanEntity->setCastShadows(false);

	mpHumanNode    = m_ogreSceneMgr->getRootSceneNode()->createChildSceneNode();
	mpHumanNode->attachObject( mpHumanEntity );
	mpHumanNode->setScale(1.0f, 1.0f, 1.0f);

	// Place the local ISB axis into a zero position in Typical
	mpHumanNode->setOrientation( Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_X ) );


	/// BONES (segments)

	//m_ogreSceneMgr->setDisplaySceneNodes(true);


	// Names in skeleton.xml
	Ogre::Bone * hipsBone      = mpHumanEntity->getSkeleton()->getBone("Hips");

	//Ogre::Bone * rHipJointBone = mpHumanEntity->getSkeleton()->getBone("RHipJoint");
	Ogre::Bone * rThighBone    = mpHumanEntity->getSkeleton()->getBone("RightUpLeg");
	Ogre::Bone * rShinBone     = mpHumanEntity->getSkeleton()->getBone("RightLeg");
	Ogre::Bone * rFootBone     = mpHumanEntity->getSkeleton()->getBone("RightFoot");

	//Ogre::Bone * lHipJointBone = mpHumanEntity->getSkeleton()->getBone("LHipJoint");
	Ogre::Bone * lThighBone    = mpHumanEntity->getSkeleton()->getBone("LeftUpLeg");
	Ogre::Bone * lShinBone     = mpHumanEntity->getSkeleton()->getBone("LeftLeg");
	Ogre::Bone * lFootBone     = mpHumanEntity->getSkeleton()->getBone("LeftFoot");


	// mBonePtrs

	mBonePtrs[0] = hipsBone;
	mBonePtrs[1] = rThighBone;
	mBonePtrs[2] = rShinBone;
	mBonePtrs[3] = rFootBone;
	mBonePtrs[4] = lThighBone;
	mBonePtrs[5] = lShinBone;
	mBonePtrs[6] = lFootBone;


	// Manual control: make them independent from skeleton animations

	for ( int iBone = 0 ; iBone <= 6 ; ++iBone)
	{

		// std style
		/*
		bones[iBone]->setManuallyControlled(true);							 // free the bone from the opression of the chain
		derivedOrientations[iBone] = bones[iBone]->_getDerivedOrientation(); // save derived orientation before freeing the bone
		bones[iBone]->setInheritOrientation(false);                          // free the bone from the inherited kinematic chain
		bones[iBone]->setOrientation( derivedOrientations[iBone] );          // restore initial derived orientation (correct display)
		*/

		// QVector style

		mBonePtrs.at(iBone)->setManuallyControlled(true);

		mDerivedOrientations[iBone] = mBonePtrs.at(iBone)->_getDerivedOrientation();
		mBonePtrs.at(iBone)->setInheritOrientation(false);
		mBonePtrs.at(iBone)->setOrientation( mDerivedOrientations.at(iBone) );

	}


	/// JOINT AXES


	float ax_gap           = 0.5f;
	float ax_height_hip    = 0.8f;
	float ax_height_knee   = 0.5f;
	float ax_height_ankle  = 0.05f;
	float ax_gap_offset    = 0.1f;

	Ogre::Vector3 axes_scale(0.1f, 0.1f, 0.1f);

	Ogre::Entity*    personAxes     = m_ogreSceneMgr->createEntity("Axes.mesh");
	Ogre::SceneNode* personAxesNode = m_ogreSceneMgr->getRootSceneNode()->createChildSceneNode();
	personAxesNode->attachObject( personAxes );
	personAxesNode->setScale(axes_scale);
	personAxesNode->setPosition  (0.5f, 0.0f, ax_height_knee);

	Ogre::Entity*    rightHipAxes     = m_ogreSceneMgr->createEntity("Axes.mesh");
	Ogre::SceneNode* rightHipAxesNode = m_ogreSceneMgr->getRootSceneNode()->createChildSceneNode();
	rightHipAxesNode->attachObject( rightHipAxes );
	rightHipAxesNode->setScale(axes_scale);
	rightHipAxesNode->setPosition  (0.0f, -ax_gap, ax_height_hip);

	Ogre::Entity*    rightKneeAxes     = m_ogreSceneMgr->createEntity("Axes.mesh");
	Ogre::SceneNode* rightKneeAxesNode = m_ogreSceneMgr->getRootSceneNode()->createChildSceneNode();
	rightKneeAxesNode->attachObject( rightKneeAxes );
	rightKneeAxesNode->setScale(axes_scale);
	rightKneeAxesNode->setPosition (0.0f, -ax_gap, ax_height_knee);

	Ogre::Entity*    rightAnkleAxes     = m_ogreSceneMgr->createEntity("Axes.mesh");
	Ogre::SceneNode* rightAnkleAxesNode = m_ogreSceneMgr->getRootSceneNode()->createChildSceneNode();
	rightAnkleAxesNode->attachObject( rightAnkleAxes );
	rightAnkleAxesNode->setScale(axes_scale);
	rightAnkleAxesNode->setPosition(0.0f, -ax_gap, ax_height_ankle);

	Ogre::Entity*    leftHipAxes     = m_ogreSceneMgr->createEntity("Axes.mesh");
	Ogre::SceneNode* leftHipAxesNode = m_ogreSceneMgr->getRootSceneNode()->createChildSceneNode();
	leftHipAxesNode->attachObject( leftHipAxes );
	leftHipAxesNode->setScale(axes_scale);
	leftHipAxesNode->setPosition   (0.0f,  ax_gap + ax_gap_offset, ax_height_hip);

	Ogre::Entity*    leftKneeAxes     = m_ogreSceneMgr->createEntity("Axes.mesh");
	Ogre::SceneNode* leftKneeAxesNode = m_ogreSceneMgr->getRootSceneNode()->createChildSceneNode();
	leftKneeAxesNode->attachObject( leftKneeAxes );
	leftKneeAxesNode->setScale(axes_scale);
	leftKneeAxesNode->setPosition  (0.0f,  ax_gap + ax_gap_offset, ax_height_knee);

	Ogre::Entity*    leftAnkleAxes     = m_ogreSceneMgr->createEntity("Axes.mesh");
	Ogre::SceneNode* leftAnkleAxesNode = m_ogreSceneMgr->getRootSceneNode()->createChildSceneNode();
	leftAnkleAxesNode->attachObject( leftAnkleAxes );
	leftAnkleAxesNode->setScale(axes_scale);
	leftAnkleAxesNode->setPosition (0.0f,  ax_gap + ax_gap_offset, ax_height_ankle);

	// Initial orientation

	Ogre::Quaternion Q_isb = Ogre::Quaternion( Ogre::Degree(90) , Ogre::Vector3::UNIT_X );

	mAxesNodePtrs[0] = rightHipAxesNode;
	mAxesNodePtrs[1] = rightKneeAxesNode;
	mAxesNodePtrs[2] = rightAnkleAxesNode;
	mAxesNodePtrs[3] = leftHipAxesNode;
	mAxesNodePtrs[4] = leftKneeAxesNode;
	mAxesNodePtrs[5] = leftAnkleAxesNode;

	mAxesNodePtrs[6] = personAxesNode;


	for( int iAxesNode = 0 ; iAxesNode <= 6 ; ++iAxesNode)
	{

		mAxesNodePtrs.at(iAxesNode)->setOrientation( Q_isb );

	}


	/// DBG

	Ogre::Entity*    testingAxes     = m_ogreSceneMgr->createEntity("Axes.mesh");
	Ogre::SceneNode* testingAxesNode = m_ogreSceneMgr->getRootSceneNode()->createChildSceneNode();
	testingAxesNode->attachObject( testingAxes );
	testingAxesNode->setScale(axes_scale);
	testingAxesNode->setPosition  (0.5f, 0.0f, ax_height_knee);

	mDbgAxes = testingAxesNode;


	// DEBUG: ALL AXES GLUED

	/*

	for( int iAxis = 0 ; iAxis <= 6 ; ++iAxis)
	{
		mAxesNodePtrs.at(iAxis)->setPosition  (0.5f, 0.0f, ax_height_knee);
	}
	*/

	// [AXDBG]

	// All in line!

	/*

	//Hips
	mAxesNodePtrs.at(0)->setPosition  (0.5f, -0.45f, ax_height_knee);
	mAxesNodePtrs.at(3)->setPosition  (0.5f, +0.45f, ax_height_knee);

	//Knees
	mAxesNodePtrs.at(1)->setPosition  (0.5f, -0.3f, ax_height_knee);
	mAxesNodePtrs.at(4)->setPosition  (0.5f, +0.3f, ax_height_knee);

	//Feet
	mAxesNodePtrs.at(2)->setPosition  (0.5f, -0.15f, ax_height_knee);
	mAxesNodePtrs.at(5)->setPosition  (0.5f, +0.15f, ax_height_knee);

	*/


}


void HumanModelPanel::eigenToOgreQuaternion(const Eigen::Quaterniond& Q_in , Ogre::Quaternion &Q_out)
{

	Q_out.w = Q_in.w();
	Q_out.x = Q_in.x();
	Q_out.y = Q_in.y();
	Q_out.z = Q_in.z();

}


void HumanModelPanel::updateModel
(

	const std::array<Eigen::Quaterniond,7>& Q_segments_new,
	const std::array<Eigen::Quaterniond,6>& Q_joints_new

)
{
	///  Frameskip

	if( mFrameSkipCounter <= (mcFrameSkip-1) )
	{
		++mFrameSkipCounter;
		return;
	}
	else
	{
		//mBufferFlush.start(10); // call it regularly
		mFrameSkipCounter = 0;
	}


	/// Quat conversion: Eigen to ogre

	for( int iQ = 0 ; iQ <= 6 ; ++iQ  )
	{
		// store in mSegmentQuats
		eigenToOgreQuaternion( Q_segments_new.at(iQ) , mSegmentQuats[iQ] );

		if( iQ <= 5 )
		{	
			// store in mJointQuats
			eigenToOgreQuaternion( Q_joints_new.at(iQ), mJointQuats[iQ] );
		}
	}

	/// Simulate input
	/*


	Ogre::Quaternion Q_isb = Ogre::Quaternion( Ogre::Degree(90) , Ogre::Vector3::UNIT_X ); // necessary


	Ogre::Quaternion hipSensorSimulator = Ogre::Quaternion( Ogre::Degree(45) , Ogre::Vector3::UNIT_Y );
					 hipSensorSimulator =  hipSensorSimulator * Ogre::Quaternion( Ogre::Degree(10) , Ogre::Vector3::UNIT_Z ) ;


	Ogre::Quaternion footSensorSimulator( Ogre::Degree(mDebugEraseMe) , Ogre::Vector3::UNIT_Z );
	*/


	/// Full human orientation

	/*
	// The human 3d model has local ISB axes (Y up, X forward)
	// Multiply by ISB initially to make it stand upright
	// Sensor rotations arrive as local changes about ISB. Must be applied also locally.

	//Use this: mpHumanNode->setOrientation( (Q_isb) * hipSensorSimulator );

	mpHumanNode->setOrientation( (Q_isb) * mSegmentQuats.at(0) );
	*/


	/// Bone orientation

	// Use segment quats (relative orientation to world, not to other joint)
	// to display correct orientation when the user spins around

	/*

	// In order to have a nice looking model, each bone starts with an arbitrary orientation.
	// These "must-set" starting orientations are saved in mDerivedOrientations.

	// Bones are childs of the Human entity. All rotations applied to the parent will also affect the children.
	// setRotation in bones is calculated with respect to parent orientation AND parent local axes:

	//	bone.setOrientation( NewOri )  means ((ParentOri * I) * NewOri) in general Quaternion math.

	// Parent axes : mBonePtrs[3]->setOrientation( testU * mDerivedOrientations[3] );  <-- useful
	// Bone axes   : mBonePtrs[3]->setOrientation( mDerivedOrientations[3] * testU );  <-- weird a.f.
	// World axes  : ???

	// Use this: mBonePtrs.at(3)->setOrientation( footSensorSimulator * mDerivedOrientations.at(3) );

	*/

	for(int iBone = 0 ; iBone <= 6 ;++iBone)
	{

		mBonePtrs.at(iBone)->setOrientation( mSegmentQuats.at(iBone) * mDerivedOrientations.at(iBone) );

	}

	/// AXES

	/*
	 *
	// Axes rotate about the world axes.
	// Axes need to be ISB'd first, then a local rotation is applied (as segments report ISB)

	// Use me?: mAxesNodePtrs.at(0)->setOrientation( (Q_isb) * hipSensorSimulator ); // Human axes
	// Use me?: mAxesNodePtrs.at(3)->setOrientation( (Q_isb) * hipSensorSimulator * footSensorSimulator ); // Foot
	*/

	// ----------------------------------------------------------------
	// Option 1 (default):
	// Axes display joint quats in ISB
	// ----------------------------------------------------------------


	for( int iAxes = 0 ; iAxes <= 5 ; ++iAxes )
	{

		Ogre::Quaternion temp = mQisb * mJointQuats.at(iAxes);

		temp.normalise();

		mAxesNodePtrs.at(iAxes)->setOrientation( temp );

	}

	/*

	// ----------------------------------------------------------------
	// Option 2: Axes display joint quats in typical convention:
	// ----------------------------------------------------------------

	for( int iAxes = 0 ; iAxes <= 5 ; ++iAxes )
	{

		// To retrieve the "typical" rotation convention:
		// un-isb the received quats (this means Qisb x Qreceived x *Qisb)

		Ogre::Quaternion Qtemp1 = mQisb * mJointQuats.at( iAxes );
		Qtemp1.normalise();

		Ogre::Quaternion Qtemp2 = Qtemp1 * mQisb.Inverse();
		Qtemp2.normalise();

		mAxesNodePtrs.at(iAxes)->setOrientation( Qtemp2 );

	}

	*/

	/*

	// --------------------------------------------------
	// Option 3: Axes display segment quats in typical convention:
	// --------------------------------------------------


	for( int iAxis = 0 ; iAxis <= 5 ; ++iAxis )
	{

		// To retrieve the "typical" rotation convention, we must un-isb the received quats
		// this means Qisb x Qreceived x *Qisb

		Ogre::Quaternion Qtemp1 = mQisb * mSegmentQuats.at( iAxis + 1 );
		Qtemp1.normalise();

		Ogre::Quaternion Qtemp2 = Qtemp1 * mQisb.Inverse();
		Qtemp2.normalise();

		mAxesNodePtrs.at(iAxis)->setOrientation( Qtemp2 );

	}

	// Don't judge my ugly code
	Ogre::Quaternion Qtemp1 = mQisb * mSegmentQuats.at(0);
	Qtemp1.normalise();
	Ogre::Quaternion Qtemp2 = Qtemp1 * mQisb.Inverse();
	Qtemp2.normalise();
	mAxesNodePtrs.at(6)->setOrientation( Qtemp2 );
	*/

}



// Frontal view

void HumanModelPanel::resetViewport()
{

	double fieldOfView = 1.5;
	m_ogreCamera->setOrthoWindow( fieldOfView , fieldOfView*1.5f );

	m_ogreCamera->setPosition( Ogre::Vector3(1.0f, -0.0f, 0.8f) );

	m_ogreCamera->setOrientation( Ogre::Quaternion(1,0,0,0) );
	m_ogreCamera->rotate( Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_Y) );
	m_ogreCamera->rotate( Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_X) );

}


// Sagittal view

void HumanModelPanel::sagittalViewport()
{

	double fieldOfView = 1.5;
	m_ogreCamera->setOrthoWindow( fieldOfView , fieldOfView*1.5f );

	m_ogreCamera->setPosition( Ogre::Vector3(0.0f, -1.0f, 0.8f) );

	m_ogreCamera->setOrientation( Ogre::Quaternion(1,0,0,0) );
	m_ogreCamera->rotate( Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_Y) );
	m_ogreCamera->rotate( Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_X) );
	m_ogreCamera->rotate( Ogre::Quaternion(Ogre::Degree(-90), Ogre::Vector3::UNIT_Z) );

}





// Not in use :)

void HumanModelPanel::debugCalibration
(
	const Eigen::Quaterniond                &Q_virtual,
	const std::array< Eigen::Quaterniond,7> &Q_sensors_raw,
	const std::array< Eigen::Quaterniond,7> &Q_sensors_ref
)
{

	// Use previously defined frameskipping
	// Proper looping is done in updateModel

	if( mFrameSkipCounter <= (mcFrameSkip-1) )
	{
		return;
	}

	// Define constants

	Ogre::Quaternion Q_isb = Ogre::Quaternion( Ogre::Degree(90) , Ogre::Vector3::UNIT_X ); // necessary


	// Create ogre placeholders

	Ogre::Quaternion Q_virtual_og   (1,0,0,0);    // Calculated in mainwindow
	Ogre::Quaternion Q_virtual_calc (1,0,0,0);    // Calculated here

	QVector<Ogre::Quaternion> Q_sensors_raw_og;
	QVector<Ogre::Quaternion> Q_sensors_ref_og;

	Q_sensors_raw_og.resize(7);
	Q_sensors_ref_og.resize(7);

	// Translate from Eigen to Ogre

	eigenToOgreQuaternion (Q_virtual, Q_virtual_og);

	for( int iSen = 0  ; iSen <= 6 ; ++iSen )
	{
		eigenToOgreQuaternion( Q_sensors_raw.at(iSen), Q_sensors_raw_og[iSen] );
		eigenToOgreQuaternion( Q_sensors_ref.at(iSen), Q_sensors_ref_og[iSen] );
	}

	/// VIRTUALITY

	//Virtual axis

	Eigen::Quaterniond Q_virtual_creator = Q_sensors_raw.at(0);

	Eigen::Vector3d world_X(1,0,0);
	Eigen::Vector3d world_Y(0,1,0);
	Eigen::Vector3d world_Z(0,0,1);

	Eigen::Vector3d vc_Z         = Q_virtual_creator * world_Z;            // Apply rotation to Z axis of the sensor
	Eigen::Vector3d vc_Z_proy_XY = vc_Z - ( vc_Z.dot(world_Z) * world_Z ); // Projection: rotated Y axis on the XY plane
	Eigen::Vector3d forward_line = vc_Z_proy_XY.normalized();              // Normalize projection to create a "forward line"

	double dotx = world_X.dot( forward_line );
	double detx = world_Z.dot( world_X.cross(forward_line) );
	double angle = std::atan2(detx,dotx);							// Determine angle between w_X and the forward line

	Eigen::AngleAxisd xToForward( angle, world_Z );
	Eigen::Quaterniond Qvirtual( xToForward );								// Construct a quat with the needed rotation

	/*
	Eigen::AngleAxisd  compensate( 15*M_PI/180 , world_Z );
	Eigen::Quaterniond QvirtualComp( compensate );
	QvirtualComp =  QvirtualComp * Qvirtual;
	Qvirtual = QvirtualComp;
	Q_virtual_og = Q_virtual_calc
	*/

	eigenToOgreQuaternion( Qvirtual, Q_virtual_calc ); //use recently calculated one


	mDbgAxes->setOrientation( Q_virtual_calc );

	//mDbgAxes->setVisible(false);

	// DEBUG: GLUED AXES

	/*
	// DBG: ALL AXIS SHOW SEGMENTS

	for(int iAxis = 0 ; iAxis <= 5 ; ++iAxis)
	{
		mAxesNodePtrs.at(iAxis)->setOrientation( mSegmentQuats.at(iAxis+1) );

	}
	*/


	/*

	for( int iAxes = 0; iAxes <= 6 ; ++iAxes)
	{
		mAxesNodePtrs.at( iAxes )->setOrientation( Q_sensors_raw_og.at(iAxes) );
	}

	*/


	/// SEGMENTALITY


	// Show the calculated segment

	Ogre::Quaternion Q_1_dif, Q_1_pre_typ, Q_1_typ, Q_1_pre_isb, Q_1_isb;
	Ogre::Quaternion Q_2_dif, Q_2_pre_typ, Q_2_typ, Q_2_pre_isb, Q_2_isb;

	int sens1 = 4;
	int sens2 = 7;

	sens1--;
	sens2--;

	// Con esto probamos que, en full callib, el sensor de la cadera apunta hacia adelante


	/*
	mAxesNodePtrs.at(6)->setOrientation( Q_sensors_raw_og.at(0) );
	mAxesNodePtrs.at(1)->setOrientation( Q_sensors_raw_og.at(sens1) );
	mAxesNodePtrs.at(4)->setOrientation( Q_sensors_raw_og.at(sens2) );
	*/

	// Revisamos las diferencias

	/*
	Q_dif  = Q_sensors_raw_og.at(sens1) * Q_sensors_ref_og.at(sens1).Inverse();
	Q_dif2 = Q_sensors_raw_og.at(sens2) * Q_sensors_ref_og.at(sens2).Inverse();

	mAxesNodePtrs.at(6)->setOrientation( Q_sensors_raw_og.at(0) );
	mAxesNodePtrs.at(1)->setOrientation( Q_dif  );
	mAxesNodePtrs.at(4)->setOrientation( Q_dif2 );
	*/

	//Diferencias con virtual

	Q_1_dif  = Q_sensors_raw_og.at(sens1) * Q_sensors_ref_og.at(sens1).Inverse();

	Q_1_dif.normalise();

	Q_1_pre_typ = Q_1_dif * Q_virtual_og;
	Q_1_pre_typ.normalise();

	Q_1_typ = Q_virtual_og.Inverse() * Q_1_pre_typ;
	Q_1_typ.normalise();

	Q_2_dif = Q_sensors_raw_og.at(sens2) * Q_sensors_ref_og.at(sens2).Inverse();
	Q_2_dif.normalise();

	Q_2_pre_typ = Q_2_dif * Q_virtual_og;
	Q_2_pre_typ.normalise();

	Q_2_typ = Q_virtual_og.Inverse() * Q_2_pre_typ;
	Q_2_typ.normalise();

	mAxesNodePtrs.at(6)->setOrientation( Q_sensors_raw_og.at(0) );

	mAxesNodePtrs.at(2)->setOrientation( Q_1_typ  );
	mAxesNodePtrs.at(5)->setOrientation( Q_2_typ );

	Q_1_pre_isb =  Q_1_typ * Q_isb;
	Q_1_pre_isb.normalise();

	Q_2_pre_isb = Q_2_typ * Q_isb;
	Q_2_pre_isb.normalise();


	Q_1_isb = Q_isb.Inverse() * Q_1_pre_isb;
	Q_1_isb.normalise();

	Q_2_isb = Q_isb.Inverse() * Q_2_pre_isb;
	Q_2_isb.normalise();

	mBonePtrs.at(3)->setOrientation( Q_1_isb * mDerivedOrientations.at(3) );
	mBonePtrs.at(6)->setOrientation( Q_2_isb * mDerivedOrientations.at(6) );


}

