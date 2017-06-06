# Move or rename the Silverapp project folder

Steps to setup OGRE3D with Qt when moving/renaming the source code folder:

- Rename the folder and the OldName.pro file.
- Remove the OldName.pro.user
- Double click the NewName.pro file,
Only check the option "Desktop Qt 5.7.0 MSVC2013 32bit" -> "Configure Project"
- Open NewName.pro, update TARGET (TARGET = NewName)
- Setup the OGRE3D specific compilation actions with QtCreator, as the [official guide](http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Setting+Up+An+Application+-+QtCreator) suggests. (A snapshot of this page has been provided under /webs_guardadas/ to prevent link rot)

The guide should be followed from "Build Settings" until, but not including, "Tutorial framework".

