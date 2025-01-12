#include <ChannelControllerFSM.h>

ChannelControllerFSM::ChannelControllerFSM (ButtonImpl* button,
    ServoMotor* servo,
    LiquidCrystal_I2C* lcd, 
    Potentiometer* pot,
    SerialComm* serialComm
    ) {
    this->button = button;
    this->servo = servo;
    this->lcd = lcd;
    this->pot = pot;
    this->serialComm = serialComm;
    this->currState = AUTOMATIC;

    this->serialComm->registerObserver(this);
    this->button->registerObserver(this);
    this->pot->registerObserver(this);

    this->lcd->init();
    this->lcd->backlight();
    this->changeGatePosition(this->servo->getPosition());
}

void ChannelControllerFSM::handleEvent(Event* ev) {
    switch (currState) {
    case AUTOMATIC:
        this->handleAutomatic(ev);
        break;
    case MANUAL:
        this->handleManual(ev);
        break;
    default:
        #ifdef DEBUG
        Serial.println("DEBUG: Default value reached in ChannelControllerFSM::handleEvent");
        #endif
        break;
    }
}

Potentiometer* ChannelControllerFSM::getPot() {
    return this->pot;
}

State ChannelControllerFSM::getCurrentState() {
    return currState;
}


void ChannelControllerFSM::handleManual(Event* ev) {
    switch (ev->getType()) {
    case BUTTON_PRESSED_EVENT:
        {
        this->currState = AUTOMATIC;
        this->changeGatePosition(this->servo->getPosition());
        #ifdef DEBUG
        Serial.println("DEBUG: State change MAN->AUT");
        #endif
        }
        break;
    case POT_CHECK_EVENT:
        {
        int servoPos = this->pot->getValue();
        this->changeGatePosition(servoPos);
        break;
        }
    default:
        #ifdef DEBUG
        Serial.println("DEBUG: Default case reached in ChannelControllerFSM::handleManual");
        #endif
        break;
    }
};

void ChannelControllerFSM::handleAutomatic(Event *ev) {
    #ifdef DEBUG
    Serial.println("DEBUG: Evento ricevuto in AUTOMATIC");
    #endif
    switch (ev->getType()) {
    case BUTTON_PRESSED_EVENT:
        {
        this->currState = MANUAL;
        #ifdef DEBUG
        Serial.println("DEBUG: State change AUT->MAN");
        #endif
        break;
        }
    case POS_RECEIVED_EVENT:
        {
        #ifdef DEBUG
        Serial.println("received position");
        #endif
        int pos = this->serialComm->getLastValue();
        this->changeGatePosition(pos);
        break;
        }
    default:
        #ifdef DEBUG
        Serial.println("DEBUG: Default case reached in ChannelControllerFSM::handleAutomatic");
        #endif
        break;
    }
}

void ChannelControllerFSM::changeGatePosition(int value){
    this->servo->changePosition(value);
    this->lcd->clear();
    this->lcd->setCursor(2,1);
    if(this->currState == AUTOMATIC)
    this->lcd->print("Automatic: ");
    else
    this->lcd->print("Manual: ");
    this->lcd->print(this->servo->getPosition());
    this->lcd->print("%");
    delay(50);
    this->serialComm->notifyUpdate(this->servo->getPosition());
}

