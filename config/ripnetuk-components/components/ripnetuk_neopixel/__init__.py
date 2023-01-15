import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID

DEPENDENCIES = ['logger', 'sensor']
AUTO_LOAD = ['ripnetuk_ui', 'sensor']

ns = cg.esphome_ns.namespace('ripnetuk_neopixel')

RipnetUkNeopixelComponent = ns.class_('RipnetUkNeopixelComponent', cg.Component)
CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(RipnetUkNeopixelComponent),
})


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    