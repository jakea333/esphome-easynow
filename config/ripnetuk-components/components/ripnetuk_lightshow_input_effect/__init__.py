import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID
from esphome.const import CONF_PIN
from esphome import pins

DEPENDENCIES = ['logger', 'ripnetuk_lightshow_core', 'ripnetuk_ui']
AUTO_LOAD = ['ripnetuk_ui']

corens = cg.esphome_ns.namespace('ripnetuk_lightshow_core')
coreclass = corens.class_('RipnetUkLightshowCoreComponent', cg.Component)

ns = cg.esphome_ns.namespace('ripnetuk_lightshow_input_effect')

BaseRipnetUkLightshowInputComponent = corens.class_('BaseRipnetUkLightshowInputComponent', cg.Component)

RipnetUkLightshowInputEffectComponent = ns.class_(
    'RipnetUkLightshowInputEffectComponent', cg.Component, BaseRipnetUkLightshowInputComponent)

CONF_SENSOR = "sensor"

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(RipnetUkLightshowInputEffectComponent),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)


