import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID

DEPENDENCIES = ['logger']

debug_ns = cg.esphome_ns.namespace('ripnetuk_clock')
RipnetUkNeopixelComponent = debug_ns.class_('RipnetUkClockComponent', cg.PollingComponent)
CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(RipnetUkNeopixelComponent),
}).extend(cv.polling_component_schema('1min'))


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
