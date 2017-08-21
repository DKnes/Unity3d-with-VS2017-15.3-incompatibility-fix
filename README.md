# Unity3d-with-VS2017-15.3-incompatibility-fix
.NET scripting backend and Visual Studio 2017.3 incompatibility.

Official solution: https://forum.unity3d.com/threads/net-scripting-backend-and-visual-studio-2017-3-incompatibility.487833/

This app is inspired by: https://forum.unity3d.com/threads/unable-to-build-even-an-empty-project.488278/#post-3184871
## Overview
This app changes all "UAP,Version=v10.0.xxx" to "UAP,Version=v10.0" in the *project.lock.json* file.
## Usage
./Unitybackendfix [Your application folder path]
