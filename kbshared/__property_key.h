
void SETPROPERTY_Key(const QString & n)
{ 
  
  {  

#ifdef RUN
#ifdef _MENUBARITEM
    if (my_qaction){

      if (n.compare("HelpContents", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::HelpContents);
      else if (n.compare("WhatsThis", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::WhatsThis);
      else if (n.compare("Open", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::Open);
      else if (n.compare("Close", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::Close);
      else if (n.compare("Save", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::Save);
      else if (n.compare("New", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::New);
      else if (n.compare("Delete", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::Delete);
      else if (n.compare("Cut", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::Cut);
      else if (n.compare("Copy", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::Copy);
      else if (n.compare("Paste", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::Paste);
      else if (n.compare("Undo", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::Undo);
      else if (n.compare("Redo", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::Redo);
      else if (n.compare("Back", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::Back);
      else if (n.compare("Forward", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::Forward);
      else if (n.compare("Refresh", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::Refresh);
      else if (n.compare("ZoomIn", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::ZoomIn);
      else if (n.compare("ZoomOut", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::ZoomOut);
      else if (n.compare("Print", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::Print);
      else if (n.compare("AddTab", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::AddTab);
      else if (n.compare("NextChild", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::NextChild);
      else if (n.compare("PreviousChild", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::PreviousChild);
      else if (n.compare("Find", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::Find);
      else if (n.compare("FindNext", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::FindNext);
      else if (n.compare("FindPrevious", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::FindPrevious);
      else if (n.compare("Replace", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::Replace);
      else if (n.compare("SelectAll", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::SelectAll);
      else if (n.compare("Bold", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::Bold);
      else if (n.compare("Italic", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::Italic);
      else if (n.compare("Underline", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::Underline);
      else if (n.compare("MoveToNextChar", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::MoveToNextChar);
      else if (n.compare("MoveToPreviousChar", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::MoveToPreviousChar);
      else if (n.compare("MoveToNextWord", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::MoveToNextWord);
      else if (n.compare("MoveToPreviousWord", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::MoveToPreviousWord);
      else if (n.compare("MoveToNextLine", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::MoveToNextLine);
      else if (n.compare("MoveToPreviousLine", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::MoveToPreviousLine);
      else if (n.compare("MoveToNextPage", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::MoveToNextPage);
      else if (n.compare("MoveToPreviousPage", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::MoveToPreviousPage);
      else if (n.compare("MoveToStartOfLine", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::MoveToStartOfLine);
      else if (n.compare("MoveToEndOfLine", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::MoveToEndOfLine);
      else if (n.compare("MoveToStartOfBlock", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::MoveToStartOfBlock);
      else if (n.compare("MoveToEndOfBlock", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::MoveToEndOfBlock);
      else if (n.compare("MoveToStartOfDocument", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::MoveToStartOfDocument);
      else if (n.compare("MoveToEndOfDocument", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::MoveToEndOfDocument);
      else if (n.compare("SelectNextChar", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::SelectNextChar);
      else if (n.compare("SelectPreviousChar", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::SelectPreviousChar);
      else if (n.compare("SelectNextWord", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::SelectNextWord);
      else if (n.compare("SelectPreviousWord", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::SelectPreviousWord);
      else if (n.compare("SelectNextLine", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::SelectNextLine);
      else if (n.compare("SelectPreviousLine", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::SelectPreviousLine);
      else if (n.compare("SelectNextPage", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::SelectNextPage);
      else if (n.compare("SelectPreviousPage", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::SelectPreviousPage);
      else if (n.compare("SelectStartOfLine", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::SelectStartOfLine);
      else if (n.compare("SelectEndOfLine", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::SelectEndOfLine);
      else if (n.compare("SelectStartOfBlock", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::SelectStartOfBlock);
      else if (n.compare("SelectEndOfBlock", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::SelectEndOfBlock);
      else if (n.compare("SelectStartOfDocument", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::SelectStartOfDocument);
      else if (n.compare("SelectEndOfBlock", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::SelectEndOfBlock);
      else if (n.compare("SelectStartOfDocument", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::SelectStartOfDocument);
      else if (n.compare("SelectEndOfDocument", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::SelectEndOfDocument);
      else if (n.compare("DeleteStartOfWord", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::DeleteStartOfWord);
      else if (n.compare("DeleteEndOfWord", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::DeleteEndOfWord);
      else if (n.compare("DeleteEndOfLine", Qt::CaseInsensitive) == 0) my_qaction->setShortcut(QKeySequence::DeleteEndOfLine);
      
      else my_qaction->setShortcut(QKeySequence(n));
    }

#else

    if (n.compare("HelpContents", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::HelpContents);
    else if (n.compare("WhatsThis", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::WhatsThis);
    else if (n.compare("Open", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::Open);
    else if (n.compare("Close", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::Close);
    else if (n.compare("Save", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::Save);
    else if (n.compare("New", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::New);
    else if (n.compare("Delete", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::Delete);
    else if (n.compare("Cut", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::Cut);
    else if (n.compare("Copy", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::Copy);
    else if (n.compare("Paste", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::Paste);
    else if (n.compare("Undo", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::Undo);
    else if (n.compare("Redo", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::Redo);
    else if (n.compare("Back", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::Back);
    else if (n.compare("Forward", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::Forward);
    else if (n.compare("Refresh", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::Refresh);
    else if (n.compare("ZoomIn", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::ZoomIn);
    else if (n.compare("ZoomOut", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::ZoomOut);
    else if (n.compare("Print", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::Print);
    else if (n.compare("AddTab", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::AddTab);
    else if (n.compare("NextChild", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::NextChild);
    else if (n.compare("PreviousChild", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::PreviousChild);
    else if (n.compare("Find", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::Find);
    else if (n.compare("FindNext", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::FindNext);
    else if (n.compare("FindPrevious", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::FindPrevious);
    else if (n.compare("Replace", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::Replace);
    else if (n.compare("SelectAll", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::SelectAll);
    else if (n.compare("Bold", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::Bold);
    else if (n.compare("Italic", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::Italic);
    else if (n.compare("Underline", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::Underline);
    else if (n.compare("MoveToNextChar", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::MoveToNextChar);
    else if (n.compare("MoveToPreviousChar", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::MoveToPreviousChar);
    else if (n.compare("MoveToNextWord", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::MoveToNextWord);
    else if (n.compare("MoveToPreviousWord", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::MoveToPreviousWord);
    else if (n.compare("MoveToNextLine", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::MoveToNextLine);
    else if (n.compare("MoveToPreviousLine", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::MoveToPreviousLine);
    else if (n.compare("MoveToNextPage", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::MoveToNextPage);
    else if (n.compare("MoveToPreviousPage", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::MoveToPreviousPage);
    else if (n.compare("MoveToStartOfLine", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::MoveToStartOfLine);
    else if (n.compare("MoveToEndOfLine", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::MoveToEndOfLine);
    else if (n.compare("MoveToStartOfBlock", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::MoveToStartOfBlock);
    else if (n.compare("MoveToEndOfBlock", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::MoveToEndOfBlock);
    else if (n.compare("MoveToStartOfDocument", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::MoveToStartOfDocument);
    else if (n.compare("MoveToEndOfDocument", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::MoveToEndOfDocument);
    else if (n.compare("SelectNextChar", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::SelectNextChar);
    else if (n.compare("SelectPreviousChar", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::SelectPreviousChar);
    else if (n.compare("SelectNextWord", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::SelectNextWord);
    else if (n.compare("SelectPreviousWord", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::SelectPreviousWord);
    else if (n.compare("SelectNextLine", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::SelectNextLine);
    else if (n.compare("SelectPreviousLine", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::SelectPreviousLine);
    else if (n.compare("SelectNextPage", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::SelectNextPage);
    else if (n.compare("SelectPreviousPage", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::SelectPreviousPage);
    else if (n.compare("SelectStartOfLine", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::SelectStartOfLine);
    else if (n.compare("SelectEndOfLine", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::SelectEndOfLine);
    else if (n.compare("SelectStartOfBlock", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::SelectStartOfBlock);
    else if (n.compare("SelectEndOfBlock", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::SelectEndOfBlock);
    else if (n.compare("SelectStartOfDocument", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::SelectStartOfDocument);
    else if (n.compare("SelectEndOfBlock", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::SelectEndOfBlock);
    else if (n.compare("SelectStartOfDocument", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::SelectStartOfDocument);
    else if (n.compare("SelectEndOfDocument", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::SelectEndOfDocument);
    else if (n.compare("DeleteStartOfWord", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::DeleteStartOfWord);
    else if (n.compare("DeleteEndOfWord", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::DeleteEndOfWord);
    else if (n.compare("DeleteEndOfLine", Qt::CaseInsensitive) == 0) setShortcut(QKeySequence::DeleteEndOfLine);
    
    else setShortcut(QKeySequence(n));  

#endif
 
#endif

    _property::SETPROPERTY_Key(n);
  }
}

