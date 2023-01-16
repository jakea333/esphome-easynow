import esphome.config_validation as cv
import esphome.codegen as cg
from esphome import pins
from esphome.components import sensor
from esphome.const import (
    CONF_ID,
    UNIT_MILLISECOND,
    STATE_CLASS_MEASUREMENT,
)

DEPENDENCIES = ['logger', 'ripnetuk_ui']
AUTO_LOAD = ['sensor', 'ripnetuk_ui']
ns = cg.esphome_ns.namespace('ripnetuk_clock')

RipnetUkClockComponent = ns.class_(
    'RipnetUkClockComponent', sensor.Sensor, cg.PollingComponent)


CONFIG_SCHEMA = cv.All(
    sensor.sensor_schema(
        RipnetUkClockComponent,
        unit_of_measurement=UNIT_MILLISECOND,
        accuracy_decimals=2,
        state_class=STATE_CLASS_MEASUREMENT,
    )
    .extend(cv.polling_component_schema("1s")),
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)
