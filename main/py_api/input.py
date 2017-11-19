from enum import Enum
from lib import *
from vector import *

class input(object):
    def get_key_down(key):
        return lib.input_get_key_down(key.value)

    def get_key_up(key):
        return lib.input_get_key_up(key.value)

    def get_key(key):
        return lib.input_get_key(key.value)

    def get_button_down(btn):
        return lib.input_get_button_down(btn.value)

    def get_button_up(btn):
        return lib.input_get_button_up(btn.value)

    def get_button(btn):
        return lib.input_get_button(btn.value)

    def get_cursor_position():
        r = vec2()
        pr = lib.input_get_cursor_position()
        r.x = pr.x
        r.y = pr.y
        return r

    def get_cursor_displacement():
        r = vec2()
        pr = lib.input_get_cursor_displacement()
        r.x = pr.x
        r.y = pr.y
        return r

class keys(Enum):
    backspace = c_int.in_dll(lib, 'keys_backspace')
    tab = c_int.in_dll(lib, 'keys_tab')
    clear = c_int.in_dll(lib, 'keys_clear')
    enter = c_int.in_dll(lib, 'keys_return')
    shift = c_int.in_dll(lib, 'keys_shift')
    control = c_int.in_dll(lib, 'keys_control')
    alt = c_int.in_dll(lib, 'keys_alt')
    pause = c_int.in_dll(lib, 'keys_pause')
    capital = c_int.in_dll(lib, 'keys_capital')
    escape = c_int.in_dll(lib, 'keys_escape')
    space = c_int.in_dll(lib, 'keys_space')
    prior = c_int.in_dll(lib, 'keys_prior')
    next = c_int.in_dll(lib, 'keys_next')
    end = c_int.in_dll(lib, 'keys_end')
    home = c_int.in_dll(lib, 'keys_home')
    left = c_int.in_dll(lib, 'keys_left')
    up = c_int.in_dll(lib, 'keys_up')
    right = c_int.in_dll(lib, 'keys_right')
    down = c_int.in_dll(lib, 'keys_down')
    select = c_int.in_dll(lib, 'keys_select')
    print = c_int.in_dll(lib, 'keys_print')
    execute = c_int.in_dll(lib, 'keys_execute')
    snapshot = c_int.in_dll(lib, 'keys_snapshot')
    insert = c_int.in_dll(lib, 'keys_insert')
    delete = c_int.in_dll(lib, 'keys_delete')
    help = c_int.in_dll(lib, 'keys_help')

    leftwin = c_int.in_dll(lib, 'keys_leftwin')
    rightwin = c_int.in_dll(lib, 'keys_rightwin')
    apps = c_int.in_dll(lib, 'keys_apps')
    sleep = c_int.in_dll(lib, 'keys_sleep')

    numpad0 = c_int.in_dll(lib, 'keys_numpad0')
    numpad1 = c_int.in_dll(lib, 'keys_numpad1')
    numpad2 = c_int.in_dll(lib, 'keys_numpad2')
    numpad3 = c_int.in_dll(lib, 'keys_numpad3')
    numpad4 = c_int.in_dll(lib, 'keys_numpad4')
    numpad5 = c_int.in_dll(lib, 'keys_numpad5')
    numpad6 = c_int.in_dll(lib, 'keys_numpad6')
    numpad7 = c_int.in_dll(lib, 'keys_numpad7')
    numpad8 = c_int.in_dll(lib, 'keys_numpad8')
    numpad9 = c_int.in_dll(lib, 'keys_numpad9')
    multiply = c_int.in_dll(lib, 'keys_multiply')
    add = c_int.in_dll(lib, 'keys_add')
    separator = c_int.in_dll(lib, 'keys_separator')
    subtract = c_int.in_dll(lib, 'keys_subtract')
    decimal = c_int.in_dll(lib, 'keys_decimal')
    divide = c_int.in_dll(lib, 'keys_divide')

    f1 = c_int.in_dll(lib, 'keys_f1')
    f2 = c_int.in_dll(lib, 'keys_f2')
    f3 = c_int.in_dll(lib, 'keys_f3')
    f4 = c_int.in_dll(lib, 'keys_f4')
    f5 = c_int.in_dll(lib, 'keys_f5')
    f6 = c_int.in_dll(lib, 'keys_f6')
    f7 = c_int.in_dll(lib, 'keys_f7')
    f8 = c_int.in_dll(lib, 'keys_f8')
    f9 = c_int.in_dll(lib, 'keys_f9')
    f10 = c_int.in_dll(lib, 'keys_f10')
    f11 = c_int.in_dll(lib, 'keys_f11')
    f12 = c_int.in_dll(lib, 'keys_f12')
    f13 = c_int.in_dll(lib, 'keys_f13')
    f14 = c_int.in_dll(lib, 'keys_f14')
    f15 = c_int.in_dll(lib, 'keys_f15')
    
    numlock = c_int.in_dll(lib, 'keys_numlock')
    scroll = c_int.in_dll(lib, 'keys_scroll')

    leftshift = c_int.in_dll(lib, 'keys_leftshift')
    rightshift = c_int.in_dll(lib, 'keys_rightshift')
    leftcontrol = c_int.in_dll(lib, 'keys_leftcontrol')
    rightcontrol = c_int.in_dll(lib, 'keys_rightcontrol')
    leftmenu = c_int.in_dll(lib, 'keys_leftmenu')
    rightmenu = c_int.in_dll(lib, 'keys_rightmenu')

    volmute = c_int.in_dll(lib, 'keys_volmute')
    voldown = c_int.in_dll(lib, 'keys_voldown')
    volup = c_int.in_dll(lib, 'keys_volup')

    n0 = c_int.in_dll(lib, 'keys_0')
    n1 = c_int.in_dll(lib, 'keys_1')
    n2 = c_int.in_dll(lib, 'keys_2')
    n3 = c_int.in_dll(lib, 'keys_3')
    n4 = c_int.in_dll(lib, 'keys_4')
    n5 = c_int.in_dll(lib, 'keys_5')
    n6 = c_int.in_dll(lib, 'keys_6')
    n7 = c_int.in_dll(lib, 'keys_7')
    n8 = c_int.in_dll(lib, 'keys_8')
    n9 = c_int.in_dll(lib, 'keys_9')
    
    a = c_int.in_dll(lib, 'keys_a')
    b = c_int.in_dll(lib, 'keys_b')
    c = c_int.in_dll(lib, 'keys_c')
    d = c_int.in_dll(lib, 'keys_d')
    e = c_int.in_dll(lib, 'keys_e')
    f = c_int.in_dll(lib, 'keys_f')
    g = c_int.in_dll(lib, 'keys_g')
    h = c_int.in_dll(lib, 'keys_h')
    i = c_int.in_dll(lib, 'keys_i')
    j = c_int.in_dll(lib, 'keys_j')
    k = c_int.in_dll(lib, 'keys_k')
    l = c_int.in_dll(lib, 'keys_l')
    m = c_int.in_dll(lib, 'keys_m')
    n = c_int.in_dll(lib, 'keys_n')
    o = c_int.in_dll(lib, 'keys_o')
    p = c_int.in_dll(lib, 'keys_p')
    q = c_int.in_dll(lib, 'keys_q')
    r = c_int.in_dll(lib, 'keys_r')
    s = c_int.in_dll(lib, 'keys_s')
    t = c_int.in_dll(lib, 'keys_t')
    u = c_int.in_dll(lib, 'keys_u')
    v = c_int.in_dll(lib, 'keys_v')
    w = c_int.in_dll(lib, 'keys_w')
    x = c_int.in_dll(lib, 'keys_x')
    y = c_int.in_dll(lib, 'keys_y')
    z = c_int.in_dll(lib, 'keys_z')

class buttons(Enum):
    left = c_int.in_dll(lib, 'buttons_left')
    right = c_int.in_dll(lib, 'buttons_right')
    middle = c_int.in_dll(lib, 'buttons_middle')
    extra1 = c_int.in_dll(lib, 'buttons_extra1')
    extra2 = c_int.in_dll(lib, 'buttons_extra2')


        
