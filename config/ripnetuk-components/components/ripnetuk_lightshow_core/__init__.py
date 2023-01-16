import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID
from esphome.const import CONF_PIN
from esphome import pins
from esphome.components import sensor

DEPENDENCIES = ['logger', 'sensor']

clockns = cg.esphome_ns.namespace('ripnetuk_clock')
RipnetUkClockComponent = clockns.class_(
    'RipnetUkClockComponent', sensor.Sensor, cg.Component)

ns = cg.esphome_ns.namespace('ripnetuk_lightshow_core')

RipnetUkLightshowCoreComponent = ns.class_(
    'RipnetUkLightshowCoreComponent', cg.Component)

BaseRipnetUkLightshowInputComponent = ns.class_(
    'BaseRipnetUkLightshowInputComponent', cg.Component)

BaseRipnetUkLightshowOutputComponent = ns.class_(
    'BaseRipnetUkLightshowOutputComponent', cg.Component)

CONF_PIXEL_COUNT = "pixel_count"
CONF_CLOCK = "clock"
CONF_INPUTS = "inputs"
CONF_OUTPUTS = "outputs"

CONF_INPUT = "input"

CONF_OUTPUT = "output"

INPUT_SCHEMA = cv.Schema({
    cv.Required(CONF_INPUT): cv.use_id(BaseRipnetUkLightshowInputComponent),
})

OUTPUT_SCHEMA = cv.Schema({
    cv.Required(CONF_OUTPUT): cv.use_id(BaseRipnetUkLightshowOutputComponent),
})

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(RipnetUkLightshowCoreComponent),
            cv.Required(CONF_PIXEL_COUNT): cv.int_,
            cv.Required(CONF_CLOCK): cv.use_id(RipnetUkClockComponent),
            cv.Required(CONF_INPUTS): cv.ensure_list(INPUT_SCHEMA),
            cv.Required(CONF_OUTPUTS): cv.ensure_list(OUTPUT_SCHEMA),
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

    for outputConf in config.get(CONF_INPUTS, []):
        input = yield cg.get_variable(outputConf[CONF_INPUT])
        cg.add(var.add_input(input))

    for outputConf in config.get(CONF_OUTPUTS, []):
        output = yield cg.get_variable(outputConf[CONF_OUTPUT])
        cg.add(var.add_output(output))
