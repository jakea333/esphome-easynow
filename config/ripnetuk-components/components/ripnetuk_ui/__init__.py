import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID

DEPENDENCIES = ['logger']

AUTO_LOAD = ['switch', 'button', 'number']

debug_ns = cg.esphome_ns.namespace('ripnetuk_ui')

RipnetUkSwitchComponent = debug_ns.class_(
    'RipnetUkSwitchComponent', cg.Component)

RipnetUkButtonComponent = debug_ns.class_(
    'RipnetUkButtonComponent', cg.Component)

RipnetUkNumberComponent = debug_ns.class_(
    'RipnetUkNumberComponent', cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(RipnetUkSwitchComponent),
    cv.GenerateID(): cv.declare_id(RipnetUkButtonComponent)
})


def to_code(config):
    #var = cg.new_Pvariable(config[CONF_ID])
    #yield cg.register_component(var, config)
    pass
