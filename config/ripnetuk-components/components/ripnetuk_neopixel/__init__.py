import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID
from esphome.const import CONF_PIN
from esphome import pins

DEPENDENCIES = ['logger', 'sensor', 'ripnetuk_ui']
AUTO_LOAD = ['sensor', 'ripnetuk_ui']
ns = cg.esphome_ns.namespace('ripnetuk_neopixel')

RipnetUkNeopixelComponent = ns.class_(
    'RipnetUkNeopixelComponent', cg.Component)

CONF_TEST = "test"

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(RipnetUkNeopixelComponent),
            cv.Required(CONF_PIN): pins.gpio_input_pin_schema,
            # cv.Required(CONF_TEST): cv.string_strict
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)

    pin = yield cg.gpio_pin_expression(config[CONF_PIN])
    cg.add(var.set_pin(pin))

    # if CONF_TEST in config:
    #     exp = cg.StructInitializer(
    #         RipnetUkNeopixelComponent,
    #         ("test", config[CONF_TEST]),
    #         # ("payload", config.get(CONF_PAYLOAD, "")),
    #         # ("qos", config[CONF_QOS]),
    #         # ("retain", config[CONF_RETAIN]),
    #     )

    #     cg.set_egg(var.add(exp))
