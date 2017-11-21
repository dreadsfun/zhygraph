from enum import Enum
from py_api.lib import capi
from py_api.vector import vec2, vec3, vec4
from ctypes import c_int

class input(object):
    def get_key_down(key):
        return capi.input_get_key_down(key.value)

    def get_key_up(key):
        return capi.input_get_key_up(key.value)

    def get_key(key):
        return capi.input_get_key(key.value)

    def get_button_down(btn):
        return capi.input_get_button_down(btn.value)

    def get_button_up(btn):
        return capi.input_get_button_up(btn.value)

    def get_button(btn):
        return capi.input_get_button(btn.value)

    def get_cursor_position():
        r = vec2()
        pr = capi.input_get_cursor_position()
        r.x = pr.x
        r.y = pr.y
        return r

    def get_cursor_displacement():
        r = vec2()
        pr = capi.input_get_cursor_displacement()
        r.x = pr.x
        r.y = pr.y
        return r

class keys(Enum):
    backspace = c_int.in_dll(capi, 'keys_backspace')
    tab = c_int.in_dll(capi, 'keys_tab')
    clear = c_int.in_dll(capi, 'keys_clear')
    enter = c_int.in_dll(capi, 'keys_return')
    shift = c_int.in_dll(capi, 'keys_shift')
    control = c_int.in_dll(capi, 'keys_control')
    alt = c_int.in_dll(capi, 'keys_alt')
    pause = c_int.in_dll(capi, 'keys_pause')
    capital = c_int.in_dll(capi, 'keys_capital')
    escape = c_int.in_dll(capi, 'keys_escape')
    space = c_int.in_dll(capi, 'keys_space')
    prior = c_int.in_dll(capi, 'keys_prior')
    next = c_int.in_dll(capi, 'keys_next')
    end = c_int.in_dll(capi, 'keys_end')
    home = c_int.in_dll(capi, 'keys_home')
    left = c_int.in_dll(capi, 'keys_left')
    up = c_int.in_dll(capi, 'keys_up')
    right = c_int.in_dll(capi, 'keys_right')
    down = c_int.in_dll(capi, 'keys_down')
    select = c_int.in_dll(capi, 'keys_select')
    print = c_int.in_dll(capi, 'keys_print')
    execute = c_int.in_dll(capi, 'keys_execute')
    snapshot = c_int.in_dll(capi, 'keys_snapshot')
    insert = c_int.in_dll(capi, 'keys_insert')
    delete = c_int.in_dll(capi, 'keys_delete')
    help = c_int.in_dll(capi, 'keys_help')

    leftwin = c_int.in_dll(capi, 'keys_leftwin')
    rightwin = c_int.in_dll(capi, 'keys_rightwin')
    apps = c_int.in_dll(capi, 'keys_apps')
    sleep = c_int.in_dll(capi, 'keys_sleep')

    numpad0 = c_int.in_dll(capi, 'keys_numpad0')
    numpad1 = c_int.in_dll(capi, 'keys_numpad1')
    numpad2 = c_int.in_dll(capi, 'keys_numpad2')
    numpad3 = c_int.in_dll(capi, 'keys_numpad3')
    numpad4 = c_int.in_dll(capi, 'keys_numpad4')
    numpad5 = c_int.in_dll(capi, 'keys_numpad5')
    numpad6 = c_int.in_dll(capi, 'keys_numpad6')
    numpad7 = c_int.in_dll(capi, 'keys_numpad7')
    numpad8 = c_int.in_dll(capi, 'keys_numpad8')
    numpad9 = c_int.in_dll(capi, 'keys_numpad9')
    multiply = c_int.in_dll(capi, 'keys_multiply')
    add = c_int.in_dll(capi, 'keys_add')
    separator = c_int.in_dll(capi, 'keys_separator')
    subtract = c_int.in_dll(capi, 'keys_subtract')
    decimal = c_int.in_dll(capi, 'keys_decimal')
    divide = c_int.in_dll(capi, 'keys_divide')

    f1 = c_int.in_dll(capi, 'keys_f1')
    f2 = c_int.in_dll(capi, 'keys_f2')
    f3 = c_int.in_dll(capi, 'keys_f3')
    f4 = c_int.in_dll(capi, 'keys_f4')
    f5 = c_int.in_dll(capi, 'keys_f5')
    f6 = c_int.in_dll(capi, 'keys_f6')
    f7 = c_int.in_dll(capi, 'keys_f7')
    f8 = c_int.in_dll(capi, 'keys_f8')
    f9 = c_int.in_dll(capi, 'keys_f9')
    f10 = c_int.in_dll(capi, 'keys_f10')
    f11 = c_int.in_dll(capi, 'keys_f11')
    f12 = c_int.in_dll(capi, 'keys_f12')
    f13 = c_int.in_dll(capi, 'keys_f13')
    f14 = c_int.in_dll(capi, 'keys_f14')
    f15 = c_int.in_dll(capi, 'keys_f15')
    
    numlock = c_int.in_dll(capi, 'keys_numlock')
    scroll = c_int.in_dll(capi, 'keys_scroll')

    leftshift = c_int.in_dll(capi, 'keys_leftshift')
    rightshift = c_int.in_dll(capi, 'keys_rightshift')
    leftcontrol = c_int.in_dll(capi, 'keys_leftcontrol')
    rightcontrol = c_int.in_dll(capi, 'keys_rightcontrol')
    leftmenu = c_int.in_dll(capi, 'keys_leftmenu')
    rightmenu = c_int.in_dll(capi, 'keys_rightmenu')

    volmute = c_int.in_dll(capi, 'keys_volmute')
    voldown = c_int.in_dll(capi, 'keys_voldown')
    volup = c_int.in_dll(capi, 'keys_volup')

    n0 = c_int.in_dll(capi, 'keys_0')
    n1 = c_int.in_dll(capi, 'keys_1')
    n2 = c_int.in_dll(capi, 'keys_2')
    n3 = c_int.in_dll(capi, 'keys_3')
    n4 = c_int.in_dll(capi, 'keys_4')
    n5 = c_int.in_dll(capi, 'keys_5')
    n6 = c_int.in_dll(capi, 'keys_6')
    n7 = c_int.in_dll(capi, 'keys_7')
    n8 = c_int.in_dll(capi, 'keys_8')
    n9 = c_int.in_dll(capi, 'keys_9')
    
    a = c_int.in_dll(capi, 'keys_a')
    b = c_int.in_dll(capi, 'keys_b')
    c = c_int.in_dll(capi, 'keys_c')
    d = c_int.in_dll(capi, 'keys_d')
    e = c_int.in_dll(capi, 'keys_e')
    f = c_int.in_dll(capi, 'keys_f')
    g = c_int.in_dll(capi, 'keys_g')
    h = c_int.in_dll(capi, 'keys_h')
    i = c_int.in_dll(capi, 'keys_i')
    j = c_int.in_dll(capi, 'keys_j')
    k = c_int.in_dll(capi, 'keys_k')
    l = c_int.in_dll(capi, 'keys_l')
    m = c_int.in_dll(capi, 'keys_m')
    n = c_int.in_dll(capi, 'keys_n')
    o = c_int.in_dll(capi, 'keys_o')
    p = c_int.in_dll(capi, 'keys_p')
    q = c_int.in_dll(capi, 'keys_q')
    r = c_int.in_dll(capi, 'keys_r')
    s = c_int.in_dll(capi, 'keys_s')
    t = c_int.in_dll(capi, 'keys_t')
    u = c_int.in_dll(capi, 'keys_u')
    v = c_int.in_dll(capi, 'keys_v')
    w = c_int.in_dll(capi, 'keys_w')
    x = c_int.in_dll(capi, 'keys_x')
    y = c_int.in_dll(capi, 'keys_y')
    z = c_int.in_dll(capi, 'keys_z')

class buttons(Enum):
    left = c_int.in_dll(capi, 'buttons_left')
    right = c_int.in_dll(capi, 'buttons_right')
    middle = c_int.in_dll(capi, 'buttons_middle')
    extra1 = c_int.in_dll(capi, 'buttons_extra1')
    extra2 = c_int.in_dll(capi, 'buttons_extra2')


        
