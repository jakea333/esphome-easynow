import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID
from esphome.components import sensor
DEPENDENCIES = ['logger']
AUTO_LOAD = ['ripnetuk_ui', 'sensor']

debug_ns = cg.esphome_ns.namespace('ripnetuk_clock')


RipnetUkNeopixelComponent = debug_ns.class_(
    'RipnetUkClockComponent', sensor.Sensor, cg.PollingComponent)

CONFIG_SCHEMA = (
    sensor.sensor_schema(RipnetUkNeopixelComponent)
    .extend(cv.COMPONENT_SCHEMA)
    .extend(cv.polling_component_schema('5s'))
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)
    