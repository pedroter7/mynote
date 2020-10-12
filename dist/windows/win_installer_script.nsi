# This belongs to MyNote, see http://github.com/pedroter7/mynote 

# Compile this with NSIS to generate a installer for MyNote

# Set compression mode
SetCompressor lzma

!define PROGNAME "MyNote"
!define PROJECTNAME "mynote"
!define VERSION "1.0"
!define DISTDIR "${PROJECTNAME}-${VERSION}"

# Install window title
Name "${PROGNAME} - ${VERSION}"
# Installer
OutFile "${PROJECTNAME}-${VERSION}.exe"

# Default install directory
InstallDir "$PROGRAMFILES64\${PROJECTNAME}"

# Pages: a directory choice and install
Page directory
Page instfiles

# Default section : install 
Section
    # Copy bin dir
    SetOutPath "$INSTDIR\bin"
    File /a /r "${DISTDIR}\bin\"

    # Copy etc dir
    SetOutPath "$INSTDIR\etc"
    File /a /r "${DISTDIR}\etc\"

    # Copy lib dir
    SetOutPath "$INSTDIR\lib"
    File /a /r "${DISTDIR}\lib\" 

    # Copy share dir
    SetOutPath "$INSTDIR\share"
    File /a /r "${DISTDIR}\share\"

    # Copy root directory files
    SetOutPath $INSTDIR
    File "${DISTDIR}\LICENSE"
    File "${DISTDIR}\README.md"
    File "${DISTDIR}\*.png"

    # Create uninstaller
    WriteUninstaller "$INSTDIR\uninstall.exe"

    # Create a menu directory and shortcuts
    CreateDirectory "$SMPROGRAMS\${PROGNAME}"  
    CreateShortCut "$SMPROGRAMS\${PROGNAME}\MyNote.lnk" "$INSTDIR\bin\mynote.exe" "" "$INSTDIR\mynote_ic_64.png"
    CreateShortCut "$SMPROGRAMS\${PROGNAME}\Uninstall MyNote.lnk" "$INSTDIR\uninstall.exe"

    # Print message
    MessageBox MB_OK "${PROGNAME} was installed to $INSTDIR."
SectionEnd

# Uninstaller section
Section "uninstall"
    # Remove start menu shortcuts
    delete "$SMPROGRAMS\${PROGNAME}\MyNote.lnk"
    delete "$SMPROGRAMS\${PROGNAME}\Uninstall MyNote.lnk"
    rmDir "$SMPROGRAMS\${PROGNAME}"

    # Remove directories recursively
    rmDir /r "$INSTDIR\bin"
    rmDir /r "$INSTDIR\etc\*"
    rmDir /r "$INSTDIR\etc"
    rmDir /r "$INSTDIR\lib\*\*"
    rmDir /r "$INSTDIR\lib\*"
    rmDir /r "$INSTDIR\lib"
    rmDir /r "$INSTDIR\share\*\*\*\*\*"
    rmDir /r "$INSTDIR\share\*\*\*\*"
    rmDir /r "$INSTDIR\share\*\*\*"
    rmDir /r "$INSTDIR\share\*\*"
    rmDir /r "$INSTDIR\share\*"
    rmDir /r "$INSTDIR\share"

    # Make sure to remove the installer
    delete "$INSTDIR\uninstall.exe"

    # and then the directory itself
    rmDir /r $INSTDIR

    # Print message
    MessageBox MB_OK "${PROGNAME} was uninstalled."
SectionEnd