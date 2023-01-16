# import esphome.config_validation as cv
# import esphome.codegen as cg
# from esphome.const import CONF_ID
# from esphome.const import CONF_PIN
# from esphome import pins
# from esphome.components import sensor

# DEPENDENCIES = ['logger', 'sensor', 'ripnetuk_ui']
# AUTO_LOAD = ['sensor', 'ripnetuk_ui']
# ns = cg.esphome_ns.namespace('ripnetuk_neopixel')

# RipnetUkNeopixelComponent = ns.class_(
#     'RipnetUkNeopixelComponent', cg.Component)

# CONF_PIXEL_COUNT = "pixel_count"
# CONF_POWER_SENSOR = "power_sensor"

# CONFIG_SCHEMA = (
#     cv.Schema(
#         {
#             cv.GenerateID(): cv.declare_id(RipnetUkNeopixelComponent),
#             cv.Required(CONF_PIN): pins.gpio_input_pin_schema,
#             cv.Required(CONF_PIXEL_COUNT): cv.int_,
#             cv.Required(CONF_POWER_SENSOR): cv.use_id(sensor.Sensor),
#         }
#     )
#     .extend(cv.COMPONENT_SCHEMA)
# )


# def to_code(config):
#     var = cg.new_Pvariable(config[CONF_ID])
#     yield cg.register_component(var, config)

#     pin = yield cg.gpio_pin_expression(config[CONF_PIN])
#     cg.add(var.set_pin(pin))

#     cg.add(var.set_pixel_count(config[CONF_PIXEL_COUNT]))
#     #cg.add(var.set_power_sensor(config[CONF_POWER_SENSOR]))

#     power_sensor = yield cg.get_variable(config[CONF_POWER_SENSOR])
#     cg.add(var.set_power_sensor(power_sensor))
