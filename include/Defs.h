#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

#include <wx/string.h>

// ID som används
const wxWindowID MAIN_FRAME_ID = -1;
const unsigned int ID_LIST_CHESSPLAYERS = 1;
const unsigned int ID_RESET_DATABASE = 2;
const unsigned int ID_IMPORT_CHESSPLAYERS = 3;
const unsigned int ID_LIST_TOURNAMENTS = 4;
const unsigned int ID_LIST_TOURNAMENT_PLAYERS = 5;
const unsigned int ID_LIST_TOURNAMENT_TIEBREAKS = 6;

//Knappar
const unsigned int XML_BUTTON_ID = 0;
const unsigned int TEXTFILE_BUTTON_ID = 1;

// Heltalskonstanter
const unsigned int MINIMUM_LENGTH = 2;
const unsigned int DEFAULT_FRAME_WIDTH = 700;
const unsigned int DEFAULT_FRAME_HEIGHT = 700;

// Textkonstanter
const wxString QUIT_MESSAGE = "Avsluta";
const wxString ABOUT_MESSAGE = "Om";
const wxString APPLICATION_NAME = "ChessPairer";
const wxString DEVELOPER_NAME = "Anders Kleimark";
const wxString DEVELOPER_EMAIL = "akleimark@gmail.com";
const wxString GENERAL_ERROR_MESSAGE = "Fel";
const wxString ADD_STRING = L"L\u00E4gg till";
const wxString EDIT_STRING = L"\u00C4ndra";
const wxString REMOVE_STRING = "Ta bort";
const wxString RESET_STRING = L"\u00C5terst\u00E4ll";
const wxString CLOSE_STRING = L"St\u00E4ng";
const wxString FORM_ERROR = L"Det finns fel i formul\u00E4ret.";
const wxString CONFIRM_MESSAGE = L"\u00C4r du s\u00E4ker p\u00E5 att du vill ";
const wxString CONFIRM_LABEL = "Svara";
const wxString SUCCESS_MESSAGE = "Klart";
const wxString NO_RESULT = "-";

#endif // DEFS_H_INCLUDED
