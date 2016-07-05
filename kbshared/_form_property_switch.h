



#ifdef SWITCH4
switch(ct){
#else
switch(SWITCH6){
#endif

  // CONTROL

#define CONTROLTYPE t_header 
#ifdef IDE
  #define SUPERCLASS _header
#elif defined(RUN)
  #define SUPERCLASS kb_header
#endif
#define CONTROLLIST headers  
#include "_form_property_switch2.h"
  
#define CONTROLTYPE t_udpsocket 
#ifdef IDE
  #define SUPERCLASS _udpsocket
#elif defined(RUN)
  #define SUPERCLASS kb_udpsocket
#endif
#define CONTROLLIST udpsockets  
#include "_form_property_switch2.h"

#define CONTROLTYPE t_serialport 
#ifdef IDE
  #define SUPERCLASS _serialport
#elif defined(RUN)
  #define SUPERCLASS kb_serialport
#endif
#define CONTROLLIST serialports  
#include "_form_property_switch2.h"

#define CONTROLTYPE t_toolbutton 
#ifdef IDE
  #define SUPERCLASS _toolbutton
#elif defined(RUN)
  #define SUPERCLASS kb_toolbutton
#endif
#define CONTROLLIST toolbuttons  
#include "_form_property_switch2.h"

#define CONTROLTYPE t_svg 
#ifdef IDE
  #define SUPERCLASS _svg 
#elif defined(RUN)
  #define SUPERCLASS kb_svg
#endif
#define CONTROLLIST svgs   
#include "_form_property_switch2.h"

#define CONTROLTYPE t_scrollbar
#ifdef IDE
  #define SUPERCLASS _scrollbar
#elif defined(RUN)
  #define SUPERCLASS kb_scrollbar
#endif
#define CONTROLLIST scrollbars   
#include "_form_property_switch2.h"

#define CONTROLTYPE t_spinbox
#ifdef IDE
  #define SUPERCLASS _spinbox
#elif defined(RUN)
  #define SUPERCLASS kb_spinbox
#endif
#define CONTROLLIST spinboxes   
#include "_form_property_switch2.h"

#define CONTROLTYPE t_slider
#ifdef IDE
  #define SUPERCLASS _slider
#elif defined(RUN)
  #define SUPERCLASS kb_slider
#endif
#define CONTROLLIST sliders   
#include "_form_property_switch2.h"

#define CONTROLTYPE t_formsview
#ifdef IDE
  #define SUPERCLASS _formsview
#elif defined(RUN)
  #define SUPERCLASS kb_formsview
#endif
#define CONTROLLIST formsviews   
#include "_form_property_switch2.h"

#define CONTROLTYPE t_toolbarview
#ifdef IDE
  #define SUPERCLASS _toolbarview
#elif defined(RUN)
  #define SUPERCLASS kb_toolbarview
#endif
#define CONTROLLIST toolbarviews   
#include "_form_property_switch2.h"

#define CONTROLTYPE t_resizebox 
#ifdef IDE
  #define SUPERCLASS _resizebox 
#elif defined(RUN)
  #define SUPERCLASS kb_resizebox 
#endif
#define CONTROLLIST resizeboxes   
#include "_form_property_switch2.h"

#define CONTROLTYPE t_line 
#ifdef IDE
  #define SUPERCLASS _line
#elif defined(RUN)
  #define SUPERCLASS kb_line
#endif
#define CONTROLLIST lines  
#include "_form_property_switch2.h"

#define CONTROLTYPE t_movie 
#ifdef IDE
  #define SUPERCLASS _movie
#elif defined(RUN)
  #define SUPERCLASS kb_movie
#endif
#define CONTROLLIST movies  
#include "_form_property_switch2.h"

#define CONTROLTYPE t_sound
#ifdef IDE
  #define SUPERCLASS _sound
#elif defined(RUN)
  #define SUPERCLASS kb_sound
#endif
#define CONTROLLIST sounds  
#include "_form_property_switch2.h"
    
#define CONTROLTYPE t_web
#ifdef IDE
  #define SUPERCLASS _web
#elif defined(RUN)
  #define SUPERCLASS kb_web
#endif
#define CONTROLLIST webs  
#include "_form_property_switch2.h"
    
#define CONTROLTYPE t_footer
#ifdef IDE
  #define SUPERCLASS _footer
#elif defined(RUN)
  #define SUPERCLASS kb_footer
#endif
#define CONTROLLIST footers  
#include "_form_property_switch2.h"
/*
#define CONTROLTYPE t_vsplit 
#ifdef IDE
  #define SUPERCLASS _vsplit
#elif defined(RUN)
  #define SUPERCLASS kb_vsplit
#endif
#define CONTROLLIST vsplits  
#include "_form_property_switch2.h"

#define CONTROLTYPE t_hsplit 
#ifdef IDE
  #define SUPERCLASS _hsplit
#elif defined(RUN)
  #define SUPERCLASS kb_hsplit
#endif
#define CONTROLLIST hsplits  
#include "_form_property_switch2.h"

#define CONTROLTYPE t_vhbox 
#ifdef IDE
  #define SUPERCLASS _vhbox
#elif defined(RUN)
  #define SUPERCLASS kb_vhbox
#endif
#define CONTROLLIST vhboxes   
#include "_form_property_switch2.h"

#define CONTROLTYPE t_hbox 
#ifdef IDE
  #define SUPERCLASS _hbox
#elif defined(RUN)
  #define SUPERCLASS kb_hbox
#endif
#define CONTROLLIST hboxes   
#include "_form_property_switch2.h"

#define CONTROLTYPE t_vbox 
#ifdef IDE
  #define SUPERCLASS _vbox
#elif defined(RUN)
  #define SUPERCLASS kb_vbox
#endif
#define CONTROLLIST vboxes   
#include "_form_property_switch2.h"
*/
#define CONTROLTYPE t_label 
#ifdef IDE
  #define SUPERCLASS _label
#elif defined(RUN)
  #define SUPERCLASS kb_label
#endif
#define CONTROLLIST labels   
#include "_form_property_switch2.h"

//#ifndef FASTMODE

#define CONTROLTYPE t_commandbutton 
#ifdef IDE
  #define SUPERCLASS _commandbutton
#elif defined(RUN)
  #define SUPERCLASS kb_commandbutton
#endif
#define CONTROLLIST commandbuttons
#include "_form_property_switch2.h"

#define CONTROLTYPE t_commandlinkbutton 
#ifdef IDE
  #define SUPERCLASS _commandlinkbutton
#elif defined(RUN)
  #define SUPERCLASS kb_commandlinkbutton
#endif
#define CONTROLLIST commandlinkbuttons
#include "_form_property_switch2.h"

#define CONTROLTYPE t_checkbox 
#ifdef IDE
  #define SUPERCLASS _checkbox
#elif defined(RUN)
  #define SUPERCLASS kb_checkbox
#endif
#define CONTROLLIST checkboxes
#include "_form_property_switch2.h"

#define CONTROLTYPE t_frame 
#ifdef IDE
  #define SUPERCLASS _frame
#elif defined(RUN)
  #define SUPERCLASS kb_frame
#endif
#define CONTROLLIST frames
#include "_form_property_switch2.h"

#define CONTROLTYPE t_listbox
#ifdef IDE
  #define SUPERCLASS _listbox
#elif defined(RUN)
  #define SUPERCLASS kb_listbox
#endif
#define CONTROLLIST listboxes
#include "_form_property_switch2.h"

#define CONTROLTYPE t_radiobutton
#ifdef IDE
  #define SUPERCLASS _radiobutton
#elif defined(RUN)
  #define SUPERCLASS kb_radiobutton
#endif
#define CONTROLLIST radiobuttons
#include "_form_property_switch2.h"

#define CONTROLTYPE t_tab
#ifdef IDE
  #define SUPERCLASS _tab
#elif defined(RUN)
  #define SUPERCLASS kb_tab
#endif
#define CONTROLLIST tabs
#include "_form_property_switch2.h"

#define CONTROLTYPE t_textbox
#ifdef IDE
  #define SUPERCLASS _textbox
#elif defined(RUN)
  #define SUPERCLASS kb_textbox
#endif
#define CONTROLLIST textboxes
#include "_form_property_switch2.h"

#define CONTROLTYPE t_progressbar
#ifdef IDE
  #define SUPERCLASS _progressbar
#elif defined(RUN)
  #define SUPERCLASS kb_progressbar
#endif
#define CONTROLLIST progressbars
#include "_form_property_switch2.h"
/*
#define CONTROLTYPE t_scrollbar
#define SUPERCLASS kb_scrollbar  
#define CONTROLLIST scrollbars
#include "_form_property_switch2.h"
*/
#define CONTROLTYPE t_image
#ifdef IDE
  #define SUPERCLASS _image
#elif defined(RUN)
  #define SUPERCLASS kb_image
#endif
#define CONTROLLIST images
#include "_form_property_switch2.h"

#define CONTROLTYPE t_timer
#ifdef IDE
  #define SUPERCLASS _timer
#elif defined(RUN)
  #define SUPERCLASS kb_timer
#endif
#define CONTROLLIST timers
#include "_form_property_switch2.h"

#define CONTROLTYPE t_treeview
#ifdef IDE
  #define SUPERCLASS _treeview
#elif defined(RUN)
  #define SUPERCLASS kb_treeview
#endif
#define CONTROLLIST treeviews
#include "_form_property_switch2.h"

#define CONTROLTYPE t_combobox
#ifdef IDE
  #define SUPERCLASS _combobox
#elif defined(RUN)
  #define SUPERCLASS kb_combobox
#endif
#define CONTROLLIST comboboxes
#include "_form_property_switch2.h"

/*
#define CONTROLTYPE t_line
#define SUPERCLASS kb_line
#define CONTROLLIST lines
#include "_form_property_switch2.h"

#define CONTROLTYPE t_rectangle
#define SUPERCLASS kb_rectangle
#define CONTROLLIST rectangles
#include "_form_property_switch2.h"

#define CONTROLTYPE t_circle
#define SUPERCLASS kb_circle
#define CONTROLLIST circles
#include "_form_property_switch2.h"
*/
/*
#define CONTROLTYPE t_hidden
#ifdef IDE
  #define SUPERCLASS _hidden
#elif defined(RUN)
  #define SUPERCLASS kb_hidden
#endif
#define CONTROLLIST hiddens
#include "_form_property_switch2.h"
*/


#define CONTROLTYPE t_imagebutton
#ifdef IDE
  #define SUPERCLASS _imagebutton
#elif defined(RUN)
  #define SUPERCLASS kb_imagebutton
#endif
#define CONTROLLIST imagebuttons
#include "_form_property_switch2.h"

/*
#define CONTROLTYPE t_activex
#define SUPERCLASS kb_activex
#define CONTROLLIST activexes
#include "_form_property_switch2.h"
*/


#define CONTROLTYPE t_box
#ifdef IDE
  #define SUPERCLASS _box
#elif defined(RUN)
  #define SUPERCLASS kb_box
#endif
#define CONTROLLIST boxes
#include "_form_property_switch2.h"

#define CONTROLTYPE t_childcontrol
#ifdef IDE
  #define SUPERCLASS _childcontrol
#elif defined(RUN)
  #define SUPERCLASS kb_childcontrol
#endif
#define CONTROLLIST childcontrols
#include "_form_property_switch2.h"

#define CONTROLTYPE t_browser
#ifdef IDE
  #define SUPERCLASS _browser
#elif defined(RUN)
  #define SUPERCLASS kb_browser
#endif
#define CONTROLLIST browsers
#include "_form_property_switch2.h"

#define CONTROLTYPE t_editor
#ifdef IDE
  #define SUPERCLASS _editor
#elif defined(RUN)
  #define SUPERCLASS kb_editor
#endif
#define CONTROLLIST editors
#include "_form_property_switch2.h"

#define CONTROLTYPE t_datebox
#ifdef IDE
  #define SUPERCLASS _datebox
#elif defined(RUN)
  #define SUPERCLASS kb_datebox
#endif
#define CONTROLLIST dateboxes
#include "_form_property_switch2.h"

#define CONTROLTYPE t_timebox
#ifdef IDE
  #define SUPERCLASS _timebox
#elif defined(RUN)
  #define SUPERCLASS kb_timebox
#endif
#define CONTROLLIST timeboxes
#include "_form_property_switch2.h"

#define CONTROLTYPE t_datetimebox
#ifdef IDE
  #define SUPERCLASS _datetimebox
#elif defined(RUN)
  #define SUPERCLASS kb_datetimebox
#endif
#define CONTROLLIST datetimeboxes
#include "_form_property_switch2.h"



/*
// OBJECT

#define CONTROLTYPE t_file
#define SUPERCLASS kb_file
#define CONTROLLIST files
#include "_form_property_switch2.h"
*/

//#endif

}

#undef SWITCH2

