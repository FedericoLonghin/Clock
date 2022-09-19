bool darkEnviroment() {
  return (analogRead(PHR_PIN) < PHR_LOWLIGHT_THRESHOLD);
}