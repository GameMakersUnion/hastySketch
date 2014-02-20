===== Steps to install HastySketch ===== 

* Prerequisites: 
- Visual Studio 2010 with Service Pack 1
- Any Git client
- OGRE 1.9
- Ogitor 0.5 (optional)


All are freely available for download.


* 1. Clone the git repository at https://github.com/GameMakersUnion/hastySketch

with your client of choice. We recommend Github for Windows for beginners, 
or SourceTree for intermediate users, or Git Bash.

* 2. Download Visual Studio 2010 Express or higher for C++, from 
http://www.visualstudio.com/downloads/download-visual-studio-vs#d-2010-express

Go to Start Menu > Windows Update > Check for Updates, wait up to a few minutes 
for all listings to update, download Visual Studio SP1 Update (approx 570MB). 
Install, reboot.

* 3. Download OGRE 1.9 SDK for Visual C++ 2010 (32-bit)
from http://www.ogre3d.org/download/sdk

or directly click: 
http://sourceforge.net/projects/ogre/files/ogre/1.9/1.9/OgreSDK_vc10_v1-9-0.exe/download

After extracting, rename the folder to "Ogre". 
Make sure the "Ogre" folder contains the "bin" folder.

Place the Ogre folder in "hastySketch\GMUOgre" (the folder that contains INSTALL.bat)
Run INSTALL.bat ; This will link OGRE to HastySketch.

Now, open HastySketch Solution file, named HastySketch.sln  
Run project so it compiles.

Happy developing!


---------------


* 4. Optionally can use Ogitor for scene editing. If you want this, do the following:

Download Ogitor from http://www.ogitor.org/ and these two zips
https://bitbucket.org/jacmoe/ogitor/downloads/media.zip
https://bitbucket.org/jacmoe/ogitor/downloads/projects.zip

It doesn't matter where you install Ogitor, we do not suggest in game project, 
to avoid committing unnecessarily.

Expand these into the folder at Ogitor/RunPath 
You can now start Ogitor by running RunPath/bin/qtOgitor.exe

Here's a guide with more in-depth instructions after setup is complete.  
https://docs.google.com/file/d/0B-BzwPAV7QvwSWVsT2kxV0NiOEk


---------------

Always run INSTALL.bat when changing Media folder structure, and HastySketch's config files. 
This can happen any time you pull changes from the repository. Ignore this if you don't know what this is! :)
