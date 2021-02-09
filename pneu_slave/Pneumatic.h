class Pneumatic {
  private:
    int pin1, pin2;
  public:
  Pneumatic (){};
    Pneumatic(int pin1, int pin2) {
      this->pin1 = pin1;
      this->pin2 = pin2;
      pinMode(pin1, OUTPUT);
      pinMode(pin2, OUTPUT);
    }

    void Close() {
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, HIGH);
    }

    void Open() {
      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, LOW);
    }

    void Free() {
      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, HIGH);
    }
};
