

class TEST2
{
public:

TEST2()
{
  bFirst[0] = false;
}

bool 		first(TEST **c, int _idx = 0)
{
  idx = _idx;
  it[idx] = list.begin();
	*c = *it[idx];
  bFirst[_idx] = it[idx] != list.end();
	return bFirst[_idx];
}

void 		reset(int nIndex = 0)
{
  bFirst[nIndex] = false;
}

bool 		next(TEST **c, int _idx = 0)
{
#ifdef _MENUBARITEM
#else
  if (bFirst[_idx] == false) return first(c, _idx);
#endif

  idx = _idx;

  ++it[idx];
	*c = *it[idx];  
  bFirst[_idx] = it[idx] != list.end();
	return bFirst[_idx];
}


bool 		isType(TEST *c)
{
  if (list3.contains(c)){
    return true;
  }
  return false;
}

bool clear()
{
  list.clear();
  list2.clear();
  list3.clear();
  list4.clear();
  list5.clear();
  return true;
}

bool readd(int no, QString old, QString s, TEST *c)
{
  if (del(old) == false) return false;
  return add(no, s, c);
}

void delRelatedWebView(QString sWebView)
{
 QMapIterator<QString, QString> i(list5);
 while (i.hasNext()) {
    i.next();

    if (!i.value().isEmpty() && i.value().compare(sWebView, Qt::CaseInsensitive) == 0){
      del(i.key());
    }
  }
}

bool add(int no, QString s, TEST *c, QString sWebView = "")
{
  if (list2.contains(s)) return false;
  sUniqueName = "";
  if (s.isEmpty()){
    uniqueName(&s);
    sUniqueName = s;
  }
  while (list.contains(no)) no++;

  list[no] = c;
  list2[s] = c;
  list3[c] = s;
  list4[c] = no;
  list5[s] = sWebView;
  return true;
}

bool del(QString s)
{
  if (list2.contains(s)){
    TEST *c = list2[s];
    int no = list4[c];

    list.remove(no);
    list2.remove(s);
    list3.remove(c);
    list4.remove(c);
    list5.remove(s);

    first(&c);

    return true;
  } 
  return false;
}

bool del2(TEST *c)
{
  if (list3.contains(c)){
    QString s = list3[c];
    int no = list4[c];

    list.remove(no);
    list2.remove(s);
    list3.remove(c);
    list4.remove(c);
    list5.remove(s);

    first(&c);

    return true;
  }
  return false;

}

t_boolean has(const QString & s)
{
  return list2.contains(s);
  
}

void uniqueName(QString *s)
{
  if (list2.contains(*s) || s->isEmpty()){
    int n = count() + 1;
    do {
      (*s).sprintf("%s%d", TEST3, n++);
    } while (list2.contains(*s));
  }
  
}

t_integer count()
{
  return list.size();
}

private:

bool bFirst[MAX_ITERATOR];

QMap<int, TEST*> list;
QMap<QString, TEST*> list2;
QMap<TEST*, QString> list3;
QMap<TEST*, int> list4;
QMap<QString, QString> list5;

QMap<int, TEST*>::ConstIterator it[MAX_ITERATOR];
int idx; // idx and MAX_ITERATOR needed for recursive calls

};


