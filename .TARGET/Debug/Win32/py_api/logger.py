from lib import *

class log:
    def debug(msg):
        lib.log_debug(msg.encode())

    def info(msg):
        lib.log_info(msg.encode())

    def warn(msg):
        lib.log_warn(msg.encode())

    def error(msg):
        lib.log_error(msg.encode())
