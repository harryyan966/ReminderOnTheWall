Set Ws = CreateObject("Scripting.FileSystemObject")
currentpath = Ws.GetFolder(".").Path

Set oWS = WScript.CreateObject("WScript.Shell")
strHome = oWS.ExpandEnvironmentStrings("%USERPROFILE%")
sLinkFile = strHome + "\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup\on-duty-noticer.lnk"

Set oLink = oWS.CreateShortcut(sLinkFile)
    oLink.TargetPath = currentpath + "\on-duty-noticer.exe"
 '  oLink.Arguments = ""
 '  oLink.WorkingDirectory = currentpath
 '  oLink.Description = "on-duty-noticer"
 '  oLink.WindowStyle = "1"   
oLink.Save

sDesktopLink = strHome + "\Desktop\on-duty-noticer.lnk"
Set Link = oWS.CreateShortcut(sDesktopLink)
    Link.TargetPath = currentpath + "\on-duty-noticer.exe"
 '  Link.Arguments = ""
 '  Link.WorkingDirectory = currentpath
 '  Link.Description = "on-duty-noticer"
 '  Link.WindowStyle = "1"   
Link.Save

msgbox "The program is added to startup list"

