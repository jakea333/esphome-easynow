import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID
from esphome.const import CONF_PIN
from esphome import pins
from esphome.components import sensor

DEPENDENCIES = ['logger', 'ripnetuk_lightshow_core', 'ripnetuk_ui']
AUTO_LOAD = ['ripnetuk_ui']

corens = cg.esphome_ns.namespace('ripnetuk_lightshow_core')
coreclass = corens.class_('RipnetUkLightshowCoreComponent', cg.Component)

ns = cg.esphome_ns.namespace('ripnetuk_lightshow_input_sensor')

RipnetUkLightshowInputSensorComponent = ns.class_(
    'RipnetUkLightshowInputSensorComponent', cg.Component)

CONF_LIGHTSHOW_CORE = "lightshow_core"
CONF_SENSOR = "sensor"

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(RipnetUkLightshowInputSensorComponent),
            cv.Required(CONF_LIGHTSHOW_CORE): cv.use_id(coreclass),
            cv.Required(CONF_SENSOR): cv.use_id(sensor.Sensor),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)

    lightshow_core = yield cg.get_variable(config[CONF_LIGHTSHOW_CORE])
    cg.add(var.set_lightshow_core(lightshow_core))

    sensor = yield cg.get_variable(config[CONF_SENSOR])
    cg.add(var.set_sensor(sensor))
