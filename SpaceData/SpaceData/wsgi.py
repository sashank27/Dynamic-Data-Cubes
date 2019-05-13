"""
WSGI config for SpaceData project.

It exposes the WSGI callable as a module-level variable named ``application``.

For more information on this file, see
https://docs.djangoproject.com/en/2.1/howto/deployment/wsgi/
"""

import os
from FastQuery import dataset
from FastQuery import datatype

print('TAKING INPUT')

star_info, cube_info = dataset.star_input()
neighbour_info = dataset.neighbour_input()

star = datatype.Star(2073.29, 2073.84, 2039.9)
print(star in star_info)
info = star_info[star]
print(info.IDX, ' ', info.IDY, ' ', info.IDZ)

# star_info = []
# cube_info = []
# neighbour_info = []

print('STARTING SERVER')

from django.core.wsgi import get_wsgi_application

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'SpaceData.settings')

application = get_wsgi_application()
