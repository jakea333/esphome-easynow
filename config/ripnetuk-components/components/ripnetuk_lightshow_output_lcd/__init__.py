import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID
from esphome import pins
from esphome.components import sensor

DEPENDENCIES = ['logger', 'ripnetuk_lightshow_core', 'ripnetuk_ui']
AUTO_LOAD = ['ripnetuk_ui']

corens = cg.esphome_ns.namespace('ripnetuk_lightshow_core')
BaseRipnetUkLightshowOutputComponent = corens.class_(
    'BaseRipnetUkLightshowOutputComponent', cg.Component)

ns = cg.esphome_ns.namespace('ripnetuk_lightshow_output_lcd')
BaseRipnetUkLightshowOutputComponent = ns.class_(
    'RipnetUkLightshowOutputLcdComponent', cg.Component, BaseRipnetUkLightshowOutputComponent)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(BaseRipnetUkLightshowOutputComponent),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
