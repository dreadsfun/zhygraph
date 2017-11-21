from py_api.lib import capi

def debug(msg):
   capi.log_debug(msg.encode())

def info(msg):
   capi.log_info(msg.encode())

def warn(msg):
   capi.log_warn(msg.encode())

def error(msg):
   capi.log_error(msg.encode())
