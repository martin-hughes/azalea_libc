import os.path

from azalea_config.default_config import *

if os.path.exists("local_config.py"):
  from local_config import *
