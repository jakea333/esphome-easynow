import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID
from esphome.const import CONF_PIN
from esphome import pins
from esphome.components import sensor

DEPENDENCIES = ['logger']

ns = cg.esphome_ns.namespace('ripnetuk_lightshow_core')

RipnetUkLightshowCoreComponent = ns.class_(
    'RipnetUkLightshowCoreComponent', cg.Component)

CONF_PIXEL_COUNT = "pixel_count"
CONF_CLOCK = "clock"

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(RipnetUkLightshowCoreComponent),
            cv.Required(CONF_PIXEL_COUNT): cv.int_,
            cv.Required(CONF_CLOCK): cv.use_id(sensor.Sensor),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)

    cg.add(var.set_pixel_count(config[CONF_PIXEL_COUNT]))

    clock = yield cg.get_variable(config[CONF_CLOCK])
    cg.add(var.set_clock(clock))
