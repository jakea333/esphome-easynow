import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID

DEPENDENCIES = ['logger']
AUTO_LOAD = ['ripnetuk_ui', 'sensor']

debug_ns = cg.esphome_ns.namespace('ripnetuk_clock')
RipnetUkNeopixelComponent = debug_ns.class_(
    'RipnetUkClockComponent', cg.PollingComponent)
CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(RipnetUkNeopixelComponent),
}).extend(cv.polling_component_schema('1s'))

# from .types import (  # noqa
#     light_ns
# )

#light_ns = cg.esphome_ns.namespace("light")


def to_code(config):
    # cg.add_define("USE_LIGHT")
    # cg.add_global(light_ns.using)
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
