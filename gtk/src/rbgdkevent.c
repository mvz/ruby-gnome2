/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/************************************************

  rbgdkevent.c -

  $Author: mutoh $
  $Date: 2003/10/14 13:35:52 $

  Copyright (C) 2002,2003 Ruby-GNOME2 Project Team
  Copyright (C) 1998-2000 Yukihiro Matsumoto,
                          Daisuke Kanda,
                          Hiroshi Igarashi
************************************************/

#include "global.h"

static VALUE gdkevents[34];

/***********************************************/

VALUE
make_gdkevent(ev)
    GdkEvent *ev;
{
    VALUE obj;
    if (ev == NULL) return Qnil;

    obj = BOXED2RVAL(ev, GDK_TYPE_EVENT);
    RBASIC(obj)->klass = gdkevents[ev->type]; /* hack */
    return obj;
}

GdkEvent*
get_gdkevent(event)
    VALUE event;
{
    return NIL_P(event) ? NULL : RVAL2BOXED(event, GDK_TYPE_EVENT);
}

/***********************************************/

/* GdkEvent Singleton Methods */
static VALUE
gdkevent_s_events_pending(self)
    VALUE self;
{
    return gdk_events_pending() ? Qtrue : Qfalse;
}

static VALUE
gdkevent_s_peek(self)
    VALUE self;
{
    return make_gdkevent(gdk_event_peek());
}

static VALUE
gdkevent_s_get(self)
    VALUE self;
{
    return make_gdkevent(gdk_event_get());
}

static VALUE
gdkevent_s_get_graphics_expose(self, window)
    VALUE self, window;
{
    return make_gdkevent(gdk_event_get_graphics_expose(GDK_WINDOW(RVAL2GOBJ(window))));
}

/* GdkEvent */
static VALUE
gdkevent_type(self)
    VALUE self;
{
    return GENUM2RVAL(get_gdkevent(self)->type, GDK_TYPE_EVENT_TYPE);
}

static VALUE
gdkevent_put(self)
    VALUE self;
{
    gdk_event_put(get_gdkevent(self));
    return Qnil;
}

static VALUE
gdkevent_get_time(self)
    VALUE self;
{
    return INT2NUM(gdk_event_get_time(get_gdkevent(self)));
}

/* GdkEventAny */
static VALUE
gdkeventany_window(self)
    VALUE self;
{
    return GOBJ2RVAL(get_gdkevent(self)->any.window);
}

static VALUE
gdkeventany_send_event(self)
    VALUE self;
{
    return get_gdkevent(self)->any.send_event ? Qtrue : Qfalse;
}

/* GdkEventKey */
static VALUE
gdkeventkey_time(self)
    VALUE self;
{
    return INT2NUM(get_gdkevent(self)->key.time);
}

static VALUE
gdkeventkey_state(self)
    VALUE self;
{
    return GFLAGS2RVAL(get_gdkevent(self)->key.state, GDK_TYPE_MODIFIER_TYPE);
}

static VALUE
gdkeventkey_keyval(self)
    VALUE self;
{
    return INT2NUM(get_gdkevent(self)->key.keyval);
}

static VALUE
gdkeventkey_length(self)
    VALUE self;
{
    return INT2NUM(get_gdkevent(self)->key.length);
}

static VALUE
gdkeventkey_string(self)
    VALUE self;
{
    return rb_str_new2(get_gdkevent(self)->key.string);
}

/* GdkEventButton */
static VALUE
gdkeventbutton_button(self)
    VALUE self;
{
    return INT2NUM(get_gdkevent(self)->button.button);
}

static VALUE
gdkeventbutton_state(self)
    VALUE self;
{
    return GFLAGS2RVAL(get_gdkevent(self)->button.state, GDK_TYPE_MODIFIER_TYPE);
}

static VALUE
gdkeventbutton_time(self)
    VALUE self;
{
    return INT2NUM(get_gdkevent(self)->button.time);
}

static VALUE
gdkeventbutton_x(self)
    VALUE self;
{
    return rb_float_new(get_gdkevent(self)->button.x);
}

static VALUE
gdkeventbutton_y(self)
    VALUE self;
{
    return rb_float_new(get_gdkevent(self)->button.y);
}

static VALUE
gdkeventbutton_x_root(self)
    VALUE self;
{
    return rb_float_new(get_gdkevent(self)->button.x_root);
}

static VALUE
gdkeventbutton_y_root(self)
    VALUE self;
{
    return rb_float_new(get_gdkevent(self)->button.y_root);
}

/* GdkEventScroll */
static VALUE
gdkeventscroll_time(self)
    VALUE self;
{
    return INT2NUM(get_gdkevent(self)->scroll.time);
}

static VALUE
gdkeventscroll_x(self)
    VALUE self;
{
    return rb_float_new(get_gdkevent(self)->scroll.x);
}

static VALUE
gdkeventscroll_y(self)
    VALUE self;
{
    return rb_float_new(get_gdkevent(self)->scroll.y);
}

static VALUE
gdkeventscroll_state(self)
    VALUE self;
{
    return GFLAGS2RVAL(get_gdkevent(self)->scroll.state, GDK_TYPE_MODIFIER_TYPE);
}

static VALUE
gdkeventscroll_direction(self)
    VALUE self;
{
    return GENUM2RVAL(get_gdkevent(self)->scroll.direction, GDK_TYPE_SCROLL_DIRECTION);
}

/* GdkEventMotion */
static VALUE
gdkeventmotion_time(self)
    VALUE self;
{
    return INT2NUM(get_gdkevent(self)->motion.time);
}

static VALUE
gdkeventmotion_x(self)
    VALUE self;
{
    return rb_float_new(get_gdkevent(self)->motion.x);
}

static VALUE
gdkeventmotion_y(self)
    VALUE self;
{
    return rb_float_new(get_gdkevent(self)->motion.y);
}

static VALUE
gdkeventmotion_x_root(self)
    VALUE self;
{
    return rb_float_new(get_gdkevent(self)->motion.x_root);
}

static VALUE
gdkeventmotion_y_root(self)
    VALUE self;
{
    return rb_float_new(get_gdkevent(self)->motion.y_root);
}

static VALUE
gdkeventmotion_state(self)
    VALUE self;
{
    return GFLAGS2RVAL(get_gdkevent(self)->motion.state, GDK_TYPE_MODIFIER_TYPE);
}

static VALUE
gdkeventmotion_is_hint(self)
    VALUE self;
{
    return INT2NUM(get_gdkevent(self)->motion.is_hint);
}

/* GdkEventVisibility */
static VALUE
gdkeventvisibility_state(self)
    VALUE self;
{
    return GENUM2RVAL(get_gdkevent(self)->visibility.state, GDK_TYPE_VISIBILITY_STATE);
}

/* GdkEventCrossing */
static VALUE
gdkeventcrossing_subwindow(self)
    VALUE self;
{
    return GOBJ2RVAL(get_gdkevent(self)->crossing.subwindow);
}

static VALUE
gdkeventcrossing_time(self)
    VALUE self;
{
    return INT2NUM(get_gdkevent(self)->crossing.time);
}

static VALUE
gdkeventcrossing_x(self)
    VALUE self;
{
    return rb_float_new(get_gdkevent(self)->crossing.x);
}

static VALUE
gdkeventcrossing_y(self)
    VALUE self;
{
    return rb_float_new(get_gdkevent(self)->crossing.y);
}

static VALUE
gdkeventcrossing_x_root(self)
    VALUE self;
{
    return rb_float_new(get_gdkevent(self)->crossing.x_root);
}

static VALUE
gdkeventcrossing_y_root(self)
    VALUE self;
{
    return rb_float_new(get_gdkevent(self)->crossing.y_root);
}

static VALUE
gdkeventcrossing_mode(self)
    VALUE self;
{
    return GENUM2RVAL(get_gdkevent(self)->crossing.mode, GDK_TYPE_CROSSING_MODE);
}

static VALUE
gdkeventcrossing_detail(self)
    VALUE self;
{
    return GENUM2RVAL(get_gdkevent(self)->crossing.detail, GDK_TYPE_NOTIFY_TYPE);
}

static VALUE
gdkeventcrossing_focus(self)
    VALUE self;
{
    return get_gdkevent(self)->crossing.focus ? Qtrue : Qfalse;
}

static VALUE
gdkeventcrossing_state(self)
    VALUE self;
{
    return GFLAGS2RVAL(get_gdkevent(self)->crossing.state, GDK_TYPE_MODIFIER_TYPE);
}


/* GdkEventFocus */
static VALUE
gdkeventfocus_in(self)
    VALUE self;
{
    return get_gdkevent(self)->focus_change.in ? Qtrue : Qfalse;
}

/* GdkEventConfigure */
static VALUE
gdkeventconfigure_x(self)
    VALUE self;
{
    return INT2NUM(get_gdkevent(self)->configure.x);
}

static VALUE
gdkeventconfigure_y(self)
    VALUE self;
{
    return INT2NUM(get_gdkevent(self)->configure.y);
}

static VALUE
gdkeventconfigure_width(self)
    VALUE self;
{
    return INT2NUM(get_gdkevent(self)->configure.width);
}

static VALUE
gdkeventconfigure_height(self)
    VALUE self;
{
    return INT2NUM(get_gdkevent(self)->configure.height);
}

/* GdkEventProperty */
static VALUE
gdkeventproperty_atom(self)
    VALUE self;
{
    return BOXED2RVAL((get_gdkevent(self)->property.atom), GDK_TYPE_ATOM);
}

static VALUE
gdkeventproperty_time(self)
    VALUE self;
{
    return INT2NUM((int)(get_gdkevent(self)->property.time));
}

static VALUE
gdkeventproperty_state(self)
    VALUE self;
{
    return GENUM2RVAL(get_gdkevent(self)->property.state, GDK_TYPE_PROPERTY_STATE);
}

/* GdkEventSelection */
static VALUE
gdkeventselection_selection(self)
    VALUE self;
{
    return BOXED2RVAL(get_gdkevent(self)->selection.selection, GDK_TYPE_ATOM);
}

static VALUE
gdkeventselection_target(self)
    VALUE self;
{
    return BOXED2RVAL(get_gdkevent(self)->selection.target, GDK_TYPE_ATOM);
}

static VALUE
gdkeventselection_property(self)
    VALUE self;
{
    return BOXED2RVAL(get_gdkevent(self)->selection.property, GDK_TYPE_ATOM);
}

static VALUE
gdkeventselection_requestor(self)
    VALUE self;
{
#ifdef GDK_NATIVE_WINDOW_POINTER
    return UINT2NUM(GPOINTER_TO_UINT(get_gdkevent(self)->selection.requestor));
#else
    return UINT2NUM(get_gdkevent(self)->selection.requestor);
#endif
}

static VALUE
gdkeventselection_time(self)
    VALUE self;
{
    return INT2NUM(get_gdkevent(self)->selection.time);
}

/* GdkEventDND */
static VALUE
gdkeventDND_context(self)
    VALUE self;
{
    return GOBJ2RVAL(get_gdkevent(self)->dnd.context);
}

static VALUE
gdkeventDND_time(self)
    VALUE self;
{
    return INT2NUM(get_gdkevent(self)->dnd.time);
}

static VALUE
gdkeventDND_x_root(self)
    VALUE self;
{
    return INT2NUM(get_gdkevent(self)->dnd.x_root);
}

static VALUE
gdkeventDND_y_root(self)
    VALUE self;
{
    return INT2NUM(get_gdkevent(self)->dnd.y_root);
}

/* GdkEventProximity */
static VALUE
gdkeventproximity_time(self)
    VALUE self;
{
    return INT2NUM(get_gdkevent(self)->proximity.time);
}

/* GdkEventClient */
static VALUE
gdkeventclient_message_type(self)
    VALUE self;
{
    return BOXED2RVAL(get_gdkevent(self)->client.message_type, GDK_TYPE_ATOM);
}

static VALUE
gdkeventclient_data_format(self)
    VALUE self;
{
    return INT2NUM(get_gdkevent(self)->client.data_format);
}

static VALUE
gdkeventclient_data_byte(self)
    VALUE self;
{
    VALUE ary = rb_ary_new2(20);
    int i;
    for (i=0; i<20; i++)
        rb_ary_push(ary, INT2FIX(get_gdkevent(self)->client.data.b[i]));

    return ary;
}

static VALUE
gdkeventclient_data_short(self)
    VALUE self;
{
    VALUE ary = rb_ary_new2(10);
    int i;
    for (i=0; i<10; i++)
        rb_ary_push(ary, INT2FIX(get_gdkevent(self)->client.data.s[i]));

    return ary;
}

static VALUE
gdkeventclient_data_long(self)
    VALUE self;
{
    VALUE ary = rb_ary_new2(5);
    int i;
    for (i=0; i<5; i++)
        rb_ary_push(ary, INT2NUM(get_gdkevent(self)->client.data.l[i]));

    return ary;
}

static VALUE
gdkeventclient_send_client_message(self, xid)
    VALUE self, xid;
{
    return gdk_event_send_client_message(
        get_gdkevent(self), NUM2INT(xid)) ? Qtrue : Qfalse;
}

static VALUE
gdkeventclient_send_clientmessage_toall(self)
    VALUE self;
{
    gdk_event_send_clientmessage_toall(get_gdkevent(self));
    return Qnil;
}

/* GdkEventWindowState */
static VALUE
gdkeventwindowstate_changed_mask(self)
    VALUE self;
{
    return GFLAGS2RVAL(((GdkEventWindowState*)get_gdkevent(self))->changed_mask, GDK_TYPE_WINDOW_STATE);
}

static VALUE
gdkeventwindowstate_new_window_state(self)
    VALUE self;
{
    return GFLAGS2RVAL(((GdkEventWindowState*)get_gdkevent(self))->new_window_state, GDK_TYPE_WINDOW_STATE);
}

/* GdkEventSetting */
static VALUE
gdkeventsetting_action(self)
    VALUE self;
{
    return GENUM2RVAL(((GdkEventSetting*)get_gdkevent(self))->action, GDK_TYPE_SETTING_ACTION);
}

static VALUE
gdkeventsetting_name(self)
    VALUE self;
{
    return CSTR2RVAL(((GdkEventSetting*)get_gdkevent(self))->name);
}

/* GdkEventExpose */
static VALUE
gdkeventexpose_area(self)
    VALUE self;
{
    return BOXED2RVAL(&get_gdkevent(self)->expose.area, GDK_TYPE_RECTANGLE);
}

static VALUE
gdkeventexpose_count(self)
    VALUE self;
{
    return INT2NUM(get_gdkevent(self)->expose.count);
}

/* MISC */
static VALUE 
gdkevent_g2r(const GValue *values)
{
    return make_gdkevent(g_value_get_boxed(&values[0]));
}

void
Init_gtk_gdk_event()
{
    VALUE ev;
    VALUE gdkEvent;
    VALUE gdkEventAny;

    gdkEvent = G_DEF_CLASS(GDK_TYPE_EVENT, "Event", mGdk);
    gdkEventAny = rb_define_class_under(mGdk, "EventAny", gdkEvent);

    gdkevents[GDK_DELETE]        = gdkEventAny;
    gdkevents[GDK_DESTROY]       = gdkEventAny;
    gdkevents[GDK_EXPOSE]        = rb_define_class_under(mGdk, "EventExpose", gdkEventAny);
    gdkevents[GDK_MOTION_NOTIFY] = rb_define_class_under(mGdk, "EventMotion", gdkEventAny);
    gdkevents[GDK_BUTTON_PRESS]  = rb_define_class_under(mGdk, "EventButton", gdkEventAny);
    gdkevents[GDK_2BUTTON_PRESS] = gdkevents[GDK_BUTTON_PRESS];
    gdkevents[GDK_3BUTTON_PRESS] = gdkevents[GDK_BUTTON_PRESS];
    gdkevents[GDK_BUTTON_RELEASE]= gdkevents[GDK_BUTTON_PRESS];
    gdkevents[GDK_KEY_PRESS]     = rb_define_class_under(mGdk, "EventKey", gdkEventAny);
    gdkevents[GDK_KEY_RELEASE]   = gdkevents[GDK_KEY_PRESS];
    gdkevents[GDK_ENTER_NOTIFY]  = rb_define_class_under(mGdk, "EventCrossing", gdkEventAny);
    gdkevents[GDK_LEAVE_NOTIFY]  = gdkevents[GDK_ENTER_NOTIFY];
    gdkevents[GDK_FOCUS_CHANGE]  = rb_define_class_under(mGdk, "EventFocus", gdkEventAny);
    gdkevents[GDK_CONFIGURE]     = rb_define_class_under(mGdk, "EventConfigure", gdkEventAny);
    gdkevents[GDK_MAP]           = gdkEventAny;
    gdkevents[GDK_UNMAP]         = gdkEventAny;
    gdkevents[GDK_PROPERTY_NOTIFY]= rb_define_class_under(mGdk, "EventProperty", gdkEventAny);
    gdkevents[GDK_SELECTION_CLEAR]= rb_define_class_under(mGdk, "EventSelection", gdkEventAny);
    gdkevents[GDK_SELECTION_REQUEST]= gdkevents[GDK_SELECTION_CLEAR];
    gdkevents[GDK_SELECTION_NOTIFY] = gdkevents[GDK_SELECTION_CLEAR];
    gdkevents[GDK_PROXIMITY_IN]  = rb_define_class_under(mGdk, "EventProximity", gdkEventAny);
    gdkevents[GDK_PROXIMITY_OUT] = gdkevents[GDK_PROXIMITY_IN];
    gdkevents[GDK_DRAG_ENTER]    = rb_define_class_under(mGdk, "EventDND", gdkEventAny);
    gdkevents[GDK_DRAG_LEAVE]    = gdkevents[GDK_DRAG_ENTER];
    gdkevents[GDK_DRAG_MOTION]   = gdkevents[GDK_DRAG_ENTER];
    gdkevents[GDK_DRAG_STATUS]   = gdkevents[GDK_DRAG_ENTER];
    gdkevents[GDK_DROP_START]    = gdkevents[GDK_DRAG_ENTER];
    gdkevents[GDK_DROP_FINISHED] = gdkevents[GDK_DRAG_ENTER];
    gdkevents[GDK_CLIENT_EVENT]  = rb_define_class_under(mGdk, "EventClient", gdkEventAny);
    gdkevents[GDK_VISIBILITY_NOTIFY] = rb_define_class_under(mGdk, "EventVisibility", gdkEventAny);
    gdkevents[GDK_NO_EXPOSE]     = rb_define_class_under(mGdk, "EventNoExpose", gdkEventAny);
    gdkevents[GDK_SCROLL]        = rb_define_class_under(mGdk, "EventScroll", gdkEventAny);
    gdkevents[GDK_WINDOW_STATE]  = rb_define_class_under(mGdk, "EventWindowState", gdkEventAny);
    gdkevents[GDK_SETTING]       = rb_define_class_under(mGdk, "EventSetting", gdkEventAny);


    /* GdkEvent */
    rb_define_method(gdkEvent, "event_type", gdkevent_type, 0);

    rb_define_singleton_method(gdkEvent, "events_pending?", gdkevent_s_events_pending, 0);
    rb_define_singleton_method(gdkEvent, "peek", gdkevent_s_peek, 0);
    rb_define_singleton_method(gdkEvent, "get", gdkevent_s_get, 0);
    rb_define_singleton_method(gdkEvent, "get_graphics_expose", 
							   gdkevent_s_get_graphics_expose, 1);
    rb_define_method(gdkEvent, "put", gdkevent_put, 0);
    rb_define_method(gdkEvent, "time", gdkevent_get_time, 0);

    /* GdkEventAny */
    rb_define_method(gdkEventAny, "window", gdkeventany_window, 0);
    rb_define_method(gdkEventAny, "send_event?", gdkeventany_send_event, 0);

    /* GdkEventKey */
    ev = gdkevents[GDK_KEY_PRESS];
    rb_define_method(ev, "time",   gdkeventkey_time, 0);
    rb_define_method(ev, "state",  gdkeventkey_state, 0);
    rb_define_method(ev, "keyval", gdkeventkey_keyval, 0);
    rb_define_method(ev, "length", gdkeventkey_length, 0);
    rb_define_method(ev, "string", gdkeventkey_string, 0);

    /* GdkEventButton */
    ev = gdkevents[GDK_BUTTON_PRESS];
    rb_define_method(ev, "button", gdkeventbutton_button, 0);
    rb_define_method(ev, "state", gdkeventbutton_state, 0);
    rb_define_method(ev, "time",   gdkeventbutton_time, 0);
    rb_define_method(ev, "x", gdkeventbutton_x, 0);
    rb_define_method(ev, "y", gdkeventbutton_y, 0);
    rb_define_method(ev, "x_root", gdkeventbutton_x_root, 0);
    rb_define_method(ev, "y_root", gdkeventbutton_y_root, 0);

    /* GdkEventScroll */
    ev = gdkevents[GDK_SCROLL];
    rb_define_method(ev, "time",   gdkeventscroll_time, 0);
    rb_define_method(ev, "x", gdkeventscroll_x, 0);
    rb_define_method(ev, "y", gdkeventscroll_y, 0);
    rb_define_method(ev, "state", gdkeventscroll_state, 0);
    rb_define_method(ev, "direction", gdkeventscroll_direction, 0);

    /* GdkScrollDirection */
    G_DEF_CLASS(GDK_TYPE_SCROLL_DIRECTION, "Direction", ev);
    G_DEF_CONSTANTS(ev, GDK_TYPE_SCROLL_DIRECTION, "GDK_SCROLL_");

    /* GdkEventMotion */
    ev = gdkevents[GDK_MOTION_NOTIFY];
    rb_define_method(ev, "time", gdkeventmotion_time, 0);
    rb_define_method(ev, "x", gdkeventmotion_x, 0);
    rb_define_method(ev, "y", gdkeventmotion_y, 0);
    rb_define_method(ev, "state", gdkeventmotion_state, 0);
    rb_define_method(ev, "hint?", gdkeventmotion_is_hint, 0);
    rb_define_method(ev, "x_root", gdkeventmotion_x_root, 0);
    rb_define_method(ev, "y_root", gdkeventmotion_y_root, 0);

    /* GdkEventExpose */
    ev = gdkevents[GDK_EXPOSE];
    rb_define_method(ev, "area", gdkeventexpose_area, 0);
    rb_define_method(ev, "count", gdkeventexpose_count, 0);

    /* GdkEventVisibility */
    ev = gdkevents[GDK_VISIBILITY_NOTIFY];
    rb_define_method(ev, "state", gdkeventvisibility_state, 0);
    /* GdkVisibilityState */
    G_DEF_CLASS(GDK_TYPE_VISIBILITY_STATE, "State", ev);
    G_DEF_CONSTANTS(ev, GDK_TYPE_VISIBILITY_STATE, "GDK_VISIBILITY_");

    /* GdkEventCrossing */
    ev = gdkevents[GDK_ENTER_NOTIFY];
    rb_define_method(ev, "subwindow", gdkeventcrossing_subwindow, 0);
    rb_define_method(ev, "time", gdkeventcrossing_time, 0);
    rb_define_method(ev, "x", gdkeventcrossing_x, 0);
    rb_define_method(ev, "y", gdkeventcrossing_y, 0);
    rb_define_method(ev, "x_root", gdkeventcrossing_x_root, 0);
    rb_define_method(ev, "y_root", gdkeventcrossing_y_root, 0);
    rb_define_method(ev, "mode", gdkeventcrossing_mode, 0);
    rb_define_method(ev, "detail", gdkeventcrossing_detail, 0);
    rb_define_method(ev, "focus?", gdkeventcrossing_focus, 0);
    rb_define_method(ev, "state", gdkeventcrossing_state, 0);
    /* GdkCrossingMode */
    G_DEF_CLASS(GDK_TYPE_CROSSING_MODE, "CrossingMode", ev);
    G_DEF_CONSTANTS(ev, GDK_TYPE_CROSSING_MODE, "GDK_CROSSING_");
    /* GdkNotifyType */
    G_DEF_CLASS(GDK_TYPE_NOTIFY_TYPE, "NotifyType", ev);
    G_DEF_CONSTANTS(ev, GDK_TYPE_NOTIFY_TYPE, "GDK_");

    /* GdkEventFocus */
    ev = gdkevents[GDK_FOCUS_CHANGE];
    rb_define_method(ev, "in?", gdkeventfocus_in, 0);

    /* GdkEventConfigure */
    ev = gdkevents[GDK_CONFIGURE];
    rb_define_method(ev, "x", gdkeventconfigure_x, 0);
    rb_define_method(ev, "y", gdkeventconfigure_y, 0);
    rb_define_method(ev, "width", gdkeventconfigure_width, 0);
    rb_define_method(ev, "height", gdkeventconfigure_height, 0);

    /* GdkEventProperty */
    ev = gdkevents[GDK_PROPERTY_NOTIFY];
    rb_define_method(ev, "atom", gdkeventproperty_atom, 0);
    rb_define_method(ev, "time", gdkeventproperty_time, 0);
    rb_define_method(ev, "state", gdkeventproperty_state, 0);
    /* GdkPropertyState */ 
    /* Notice! You cant use Gdk::Property::DELETE 
       because it has defined by Gdk::Event already. */
    G_DEF_CLASS(GDK_TYPE_PROPERTY_STATE, "State", ev);
    G_DEF_CONSTANTS(ev, GDK_TYPE_PROPERTY_STATE, "GDK_");

    /* GdkEventSelection */
    ev = gdkevents[GDK_SELECTION_CLEAR];
    rb_define_method(ev, "selection", gdkeventselection_selection, 0);
    rb_define_method(ev, "target", gdkeventselection_target, 0);
    rb_define_method(ev, "property", gdkeventselection_property, 0);
    rb_define_method(ev, "requestor", gdkeventselection_requestor, 0);
    rb_define_method(ev, "time", gdkeventselection_time, 0);

    /* GdkEventDND */
    ev = gdkevents[GDK_DRAG_ENTER];
    rb_define_method(ev, "context", gdkeventDND_context, 0);
    rb_define_method(ev, "time", gdkeventDND_time, 0);
    rb_define_method(ev, "x_root", gdkeventDND_x_root, 0);
    rb_define_method(ev, "y_root", gdkeventDND_y_root, 0);

    /* GdkEventProximity */
    ev = gdkevents[GDK_PROXIMITY_IN];
    rb_define_method(ev, "time", gdkeventproximity_time, 0);

    /* GdkEventClient */
    ev = gdkevents[GDK_CLIENT_EVENT];
    rb_define_method(ev, "message_type", gdkeventclient_message_type, 0);
    rb_define_method(ev, "data_format", gdkeventclient_data_format, 0);
    rb_define_method(ev, "data_byte", gdkeventclient_data_byte, 0);
    rb_define_method(ev, "data_short", gdkeventclient_data_short, 0);
    rb_define_method(ev, "data_long", gdkeventclient_data_long, 0);
    rb_define_method(ev, "send_client_message", 
					 gdkeventclient_send_client_message, 1);
    rb_define_method(ev, "send_clientmessage_toall", 
					 gdkeventclient_send_clientmessage_toall, 0);
    rb_define_alias(ev, "send_client_message_toall",
					"send_clientmessage_toall");

    /* GdkEventNoExpose */

    /* GdkEventWindowState */
    ev = gdkevents[GDK_WINDOW_STATE];
    rb_define_method(ev, "changed_mask", gdkeventwindowstate_changed_mask, 0);
    rb_define_method(ev, "new_window_state", gdkeventwindowstate_new_window_state, 0);
    /* GdkWindowState */
    G_DEF_CLASS(GDK_TYPE_WINDOW_STATE, "WindowState", ev);
    G_DEF_CONSTANTS(ev, GDK_TYPE_WINDOW_STATE, "GDK_WINDOW_STATE_");

    /* GdkEventSetting */
    ev = gdkevents[GDK_SETTING];
    rb_define_method(ev, "action", gdkeventsetting_action, 0);
    rb_define_method(ev, "name", gdkeventsetting_name, 0);
    /* GdkSettingAction */
    G_DEF_CLASS(GDK_TYPE_SETTING_ACTION, "SettingAction", mGdk);
    G_DEF_CONSTANTS(mGdk, GDK_TYPE_SETTING_ACTION, "GDK_SETTING_");

    rbgobj_register_g2r_func(GDK_TYPE_EVENT, &gdkevent_g2r);

    /*
     * GdkEvent's Constants
     */
    rb_define_const(gdkEvent, "CURRENT_TIME", INT2FIX(GDK_CURRENT_TIME));
    rb_define_const(gdkEvent, "PRIORITY_EVENTS", INT2FIX(GDK_PRIORITY_EVENTS));

    /* GdkEventType */
    /* XXX */
    G_RENAME_CONSTANT("2BUTTON_PRESS","BUTTON2_PRESS");
    G_RENAME_CONSTANT("3BUTTON_PRESS","BUTTON3_PRESS");
    G_DEF_CLASS(GDK_TYPE_EVENT_TYPE, "Type", gdkEvent);
    G_RENAME_CONSTANT("2BUTTON_PRESS","BUTTON2_PRESS");
    G_RENAME_CONSTANT("3BUTTON_PRESS","BUTTON3_PRESS");
    G_DEF_CONSTANTS(gdkEvent, GDK_TYPE_EVENT_TYPE, "GDK_");

    /* GdkEventMask */
    G_DEF_CLASS(GDK_TYPE_EVENT_MASK, "Mask", gdkEvent);
    G_DEF_CONSTANTS(gdkEvent, GDK_TYPE_EVENT_MASK, "GDK_");
}
