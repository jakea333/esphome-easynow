import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID
from esphome.const import CONF_PIN
from esphome import pins
from esphome.components import sensor

DEPENDENCIES = ['logger', 'ripnetuk_lightshow_core', 'ripnetuk_ui']
AUTO_LOAD = ['ripnetuk_ui']

corens = cg.esphome_ns.namespace('ripnetuk_lightshow_core')
# coreclass = corens.class_('RipnetUkLightshowCoreComponent', cg.Component)
BaseRipnetUkLightshowOutputComponent = corens.class_('BaseRipnetUkLightshowOutputComponent', cg.Component)

ns = cg.esphome_ns.namespace('ripnetuk_lightshow_output_neopixel')

RipnetUkLightshowOutputNeopixelComponent = ns.class_(
    'RipnetUkLightshowOutputNeopixelComponent', cg.Component, BaseRipnetUkLightshowOutputComponent)

# CONF_LIGHTSHOW_CORE = "lightshow_core"

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(RipnetUkLightshowOutputNeopixelComponent),
            cv.Required(CONF_PIN): pins.gpio_input_pin_schema,
            # cv.Required(CONF_LIGHTSHOW_CORE): cv.use_id(coreclass),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)

    # lightshow_core = yield cg.get_variable(config[CONF_LIGHTSHOW_CORE])
    # cg.add(var.set_lightshow_core(lightshow_core))
