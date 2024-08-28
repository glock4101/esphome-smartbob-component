"""SmartBOB ESPHome Component"""

from esphome import core

def setup():
    core.add_component('smartbob', 'smartbob_component.SmartBOBComponent')
