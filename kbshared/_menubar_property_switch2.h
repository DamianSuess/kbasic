

#ifdef SWITCH5
  case CONTROLTYPE:
    (CONTROLLIST).SWITCH5
    break;
#else
  #ifdef SWITCH4
    case CONTROLTYPE:
      SWITCH3 = new SUPERCLASS SWITCH4
      break;
  #else
    #ifdef SWITCH3
      case CONTROLTYPE:
       SWITCH3 = ((SUPERCLASS *)c)->SWITCH
       #ifdef SWITCH2
       SWITCH3 = ((SUPERCLASS *)c)->SWITCH2
       #endif
       break;
    #else
      case CONTROLTYPE:
       ((SUPERCLASS *)c)->SWITCH
       #ifdef SWITCH2
       ((SUPERCLASS *)c)->SWITCH2
       #endif
       break;
    #endif
  #endif
#endif

