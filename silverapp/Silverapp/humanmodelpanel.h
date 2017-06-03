#ifndef HUMANMODELPANEL_H
#define HUMANMODELPANEL_H

#include "ogre3d_userlib/qtogrewindow.h"
//#include "ogre3d_userlib/OgreGpuCommandBufferFlush.h"

#include <QVector>

#define EIGEN_DONT_ALIGN_STATICALLY
#include <Eigen/Geometry>

class HumanModelPanel : public QTOgreWindow
{

	Q_OBJECT

public:

	explicit HumanModelPanel(QWidget *parent = NULL);
	~HumanModelPanel();

	virtual void createScene();
	void closeEvent(QCloseEvent * event);

	void setConnectionToMainWindow(const QMetaObject::Connection& connection);

private:

	Ogre::SceneNode* mpHumanNode;
	Ogre::Entity*    mpHumanEntity;

	QVector<Ogre::Bone*>      mBonePtrs;            // size 7
	QVector<Ogre::Quaternion> mDerivedOrientations; // size 7

	QVector<Ogre::SceneNode*> mAxesNodePtrs;        // size 7


	Ogre::Quaternion mQisb;
	QVector<Ogre::Quaternion> mSegmentQuats; // size 7
	QVector<Ogre::Quaternion> mJointQuats; // size 7

	Ogre::SceneNode* mDbgAxes;

	const int mcFrameSkip = 4;
	int mFrameSkipCounter = 0;

	/// Avoid input lag
	// http://www.ogre3d.org/tikiwiki/FlushGPUBuffer&structure=Cookbook

	//Ogre::GpuCommandBufferFlush mBufferFlush;

	QMetaObject::Connection mConnectionToMainWindow;

	void eigenToOgreQuaternion(const Eigen::Quaterniond& Q_in , Ogre::Quaternion &Q_out);

protected:

	 bool eventFilter(QObject *obj, QEvent *event);

public slots:


	 void updateModel
	 (
		 const std::array<Eigen::Quaterniond,7>& Q_segments_new,
		 const std::array<Eigen::Quaterniond,6>& Q_joints_new

	 );

	 void debugCalibration(
		 const Eigen::Quaterniond                &Q_virtual,
		 const std::array< Eigen::Quaterniond,7> &Q_sensors_raw,
		 const std::array< Eigen::Quaterniond,7> &Q_sensors_ref
	 );

	 void resetViewport();
	 void sagittalViewport();


};

#endif // HUMANMODELPANEL_H
