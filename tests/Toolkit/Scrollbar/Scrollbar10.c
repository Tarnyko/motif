/* 
 * Motif
 *
 * Copyright (c) 1987-2012, The Open Group. All rights reserved.
 *
 * These libraries and programs are free software; you can
 * redistribute them and/or modify them under the terms of the GNU
 * Lesser General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * These libraries and programs are distributed in the hope that
 * they will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with these librararies and programs; if not, write
 * to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301 USA
*/ 
/* 
 * HISTORY
*/ 
#ifdef REV_INFO
#ifndef lint
static char rcsid[] = "$TOG: Scrollbar10.c /main/8 1999/01/15 12:37:25 jff $"
#endif
#endif
/*
*  (c) Copyright 1987, 1988, 1989 HEWLETT-PACKARD COMPANY */
/************************************************************************
 *
 *  Create a vertical scrollbar and test SetValue for some invalid
 *  data.  Ensure that the redisplay is correct.
 *
 ************************************************************************/

#include <X11/StringDefs.h>
#include <testlib.h>

static void ScrollCallback();

void DumpData(sbw)
Widget sbw;

{
   Arg args[10];
   int n;
   int minimum;
   int maximum;
   int value;
   int slider_size;
   
   n = 0;
   XtSetArg(args[n], XmNminimum, &minimum);	n++;
   XtSetArg(args[n], XmNmaximum, &maximum);	n++;
   XtSetArg(args[n], XmNvalue, &value);		n++;
   XtSetArg(args[n], XmNsliderSize, &slider_size);	n++;
   XtGetValues(sbw, args, n);
   printf("min = %d,   max = %d,   value = %d,  slider size = %d\n\n",
            minimum, maximum, value, slider_size);
}



void main(argc, argv)
unsigned int argc;
char **argv;
{
  Widget frame;
  Widget scrollbar;
  Arg args[10];
  int n,i;

  CommonTestInit(argc, argv);

  frame = XmCreateFrame(Shell1, "frame", NULL, 0);
  XtManageChild(frame);

  n = 0;
  XtSetArg(args[n], XmNorientation, XmVERTICAL);		n++;
  XtSetArg(args[n], XmNheight, 400);		n++;
  scrollbar = XmCreateScrollBar(frame, "scrollbar", args, n);
  XtManageChild(scrollbar);
  XtRealizeWidget(Shell1);
  DumpData(scrollbar);
  CommonPause();

  printf("changing the slider size to 40 and value to 70\n");
  n = 0;
  XtSetArg(args[n], XmNsliderSize, 40);	n++;
  XtSetArg(args[n], XmNvalue, 70);		n++;
  XtSetValues(scrollbar, args, n);
  DumpData(scrollbar);
  CommonPause();

  printf("changing the maximum to 90 and value to 60\n");
  n = 0;
  XtSetArg(args[n], XmNmaximum, 90);	n++;
  XtSetArg(args[n], XmNvalue, 60);	n++;
  XtSetValues(scrollbar, args, n);
  DumpData(scrollbar);
  CommonPause();

  printf("changing the value to 50\n");
  n = 0;
  XtSetArg(args[n], XmNvalue, 50);	n++;
  XtSetValues(scrollbar, args, n);
  DumpData(scrollbar);
  CommonPause();

  printf("changing the maximum to 80\n");
  n = 0;
  XtSetArg(args[n], XmNmaximum, 80);	n++;
  XtSetValues(scrollbar, args, n);
  DumpData(scrollbar);
  CommonPause();

  printf("changing the value to 0 and the min to 10\n");
  n = 0;
  XtSetArg(args[n], XmNvalue, 0);	n++;
  XtSetArg(args[n], XmNminimum, 10);	n++;
  XtSetValues(scrollbar, args, n);
  DumpData(scrollbar);
  CommonPause();

  printf("changing the min to 20\n");
  n = 0;
  XtSetArg(args[n], XmNminimum, 20);	n++;
  XtSetValues(scrollbar, args, n);
  DumpData(scrollbar);

  XtAddCallback(scrollbar, XmNvalueChangedCallback,  ScrollCallback, NULL);
  XtAddCallback(scrollbar, XmNhelpCallback,          ScrollCallback, NULL);

  CommonPause();
  
  XtDestroyWidget(scrollbar);
  XtDestroyWidget(frame);
  CommonPause();
  XtAppMainLoop(app_context);
}

static void ScrollCallback(sbw, closure, call_data)
XmScrollBarWidget sbw;
caddr_t closure;
caddr_t call_data;
{
  int value;
  int reason;
  int pixel;
  Arg args[10];
  int n;

  XmScrollBarCallbackStruct * call_value = 
    (XmScrollBarCallbackStruct *) call_data;

  reason = call_value -> reason;
  value = call_value -> value;
  pixel = call_value -> pixel;

  switch(reason)
    {
    case XmCR_VALUE_CHANGED:
      printf("Reason = XmCR_VALUE_CHANGED,	Value = %d", value);
      break;

    case XmCR_HELP:
      printf("Reason = XmCR_HELP,	Value = %d\n", value);
      break;

    default:
      printf("Hit the default, incorrect reason sent!!\n");
      break;
    }

  n = 0;
  XtSetArg(args[n], XmNvalue, &value);	n++;
  XtGetValues((Widget) sbw, args, n);
  printf(",   GetValues value = %d\n", value);
}
