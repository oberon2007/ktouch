/***************************************************************************
 *   ktouchsettings.h                                                      *
 *   ----------------                                                      *
 *   Copyright (C) 2000 by Håvard Frøiland, 2004 by Andreas Nicolai        *
 *   ghorwin@users.sourceforge.net                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef KTOUCHCONFIGURATION_H
#define KTOUCHCONFIGURATION_H

#include <vector>

#include <kurl.h>
#include <qcolor.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qfont.h>

#include "ktouchcolorscheme.h"

/// The KTouch configuration object.
///
/// There should be only one configuration object in the program so this class
/// is a singleton. That means you cannot create instances from it. The one and
/// only instance of the configuration object can be retrieved by the function
/// KTouchConfig() which returns a reference to the configuration object.<p>
/// Wherever you need to access the configuration data you can simply
/// include this file and use for example
/// @code
///  if (KTouchConfig().m_errorBeep)
///     makeSomeNoise();
/// @endcode
/// <p>The configuration data is read once (at startup) and will be written
/// whenever you quit the preferences dialog with "Ok", hit the "Apply" button
/// in the preferences dialog and quit the program. The member functions
/// for reading and writing the config data are readConfiguration() and 
/// writeConfiguration().
class KTouchConfiguration {
  public:
    /// Possible types for the key hightlighting/animation method.
    enum KeyAnimation_t {
        KA_NONE,
        KA_SHADE,
        KA_SQUARE,
        KA_CIRCLE,
        NUM_KA
    };
  
    /// Reads the configuration data (preferences) from the config file.
    /// Apart from reading the configuration data it builds the lists of 
    /// lecture files, keyboard layouts and colour schemes that are available.
    void readConfiguration(QWidget * window);
    /// Stores the configuration data (preferences) in the config file
    void writeConfiguration();

    // *** Public member variables ***
    QStringList     m_lectureFiles;         	///< A list of all default lecture files.
    QStringList     m_lectureTitles;        	///< A list of the titles of all default lecture files.
    QString			m_currentLectureFile;		///< Contains the current lecture file.
	
	QStringList     m_examinationFiles;     	///< A list of all default examination files.
	QStringList     m_examinationTitles;    	///< A list of the titles of all default examination files.
    QString			m_currentExaminationFile;	///< Contains the current examination file.
	
    QStringList     m_keyboardFiles;        	///< A list of all default keyboard layout files.
    QStringList     m_keyboardTitles;       	///< A list of the titles of all default keyboard layout files.
    QString         m_currentKeyboardFile;		///< The currently chosen keyboard layout file.
	
    unsigned int    m_currentColorScheme;   	///< Indicates which colour scheme will be used.
    bool            m_useSessionManagement; 	///< Indicates whether session management is to be used or not.
    bool            m_firstRun;             	///< Indicates that KTouch is run for the first time.
    QFont           m_slidingFont;          	///< Font for the sliding line.
    unsigned int    m_slidingDelay;         	///< Delay factor for sliding (the higher the slower).

    KTouchColorScheme               m_colors;        ///< The current colour scheme.
    QValueList<KTouchColorScheme>   m_colorSchemes;  ///< Contains all colour schemes.



    // *** old stuff ***    
    
    // general options
    QFont           m_font;             ///< The font to be used in the slide lines.

    // keyboard page
    int             m_keyAnimationType; ///< What kind of key highlighting would you like to have.
    QFont           m_keyboardFont;     ///< The keyboard font

    // other stuff not in the preferences dialog
    QValueList<KTouchKeyboardColor> m_keyboardColors;   ///< A vector holding the colour schemes for the keyboard.
    unsigned int    m_keyboardColorScheme;              ///< Indicates which colour scheme will be used.

        
/*    
    // *** new stuff - to be implemented ***
 
    // general options
    bool            m_errorBeep;        ///< Whether to beep on error or not.
    bool            m_levelBeep;        ///< Whether to make a sound on level change or not.
    QFont           m_font;             ///< The font to be used in the slide lines.
    int             m_slideSpeed;       ///< The sliding speed (must be greater or equal 1, which means 'immediately').
    bool            m_rememberLevel;    ///< If true, the old level will be set when starting KTouch normally.
    bool            m_startupPractice;  ///< If true, KTouch will start up normally in practice mode.
    
    // training page
    bool            m_autoLevelChange;  ///< Whether to use automatic level change or not.
    int             m_downCorrectLimit; ///< If user types less correct, the level will be descreased.
    int             m_downSpeedLimit;   ///< If user types slower, the level will be descreased.
    int             m_upCorrectLimit;   ///< If user types more correct, the level will be increased.
    int             m_upSpeedLimit;     ///< If user types faster, the level will be increased.

    // keyboard page
    bool            m_useColorKeys;     ///< Whether to use colours on the keys or not.
    int             m_keyAnimationType; ///< What kind of key highlighting would you like to have.
    QString         m_keyboardLayout;   ///< The currently chosen keyboard layout.
    QStringList     m_keyboardLayouts;  ///< The list of available keyboard layouts.
    QStringList     m_keyboardFiles;    ///< The list of available keyboard layout files.
    bool            m_showAnimation;    ///< If the keyboard shoud animate keys or not.
    QFont           m_keyboardFont;     ///< The keyboard font

*/    
    
  private:
    /// Recreates the lists of training lectures, keyboard layouts and colour schemes
    void updateFileLists(QWidget * window);
    /// Creates some default keyboard colors.
    void createDefaultKeyboardColors();
    
    /// We hide our constructor so that only our friend KTouchConfig()
    /// can create the config object.
    KTouchConfiguration() {};
    /// Hide the copy constructor (we want only ONE config object).
    KTouchConfiguration(const KTouchConfiguration&);
    /// This function returns our one and only settings object.
    friend KTouchConfiguration& KTouchConfig();
};

/// Returns a pointer to the global settings object.
KTouchConfiguration& KTouchConfig();

#endif  // KTOUCHCONFIGURATION_H
