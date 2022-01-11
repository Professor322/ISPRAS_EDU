import java.util.Timer;
import java.util.TimerTask;

public class PhoneLine {
    private PhoneLineContext _fsm;

    private String _response;

    private Timer _timer;

    private TimerTask _timerTask;

    public PhoneLine() {
        _fsm = new PhoneLineContext(this);
    }

    public PhoneLineContext getContext() {
        return _fsm;
    }


    public String offHook() {
        _fsm.offHook();
        return _response;
    }
    public String onHook() {
        _fsm.onHook();
        return _response;
    }

    public String validNumber() {
        _fsm.validNumber();
        //throw new RuntimeException("Not Implemented!");
        return _response;
    }

    public String invalidNumber() {
        _fsm.invalidNumber();
        //throw new RuntimeException("Not Implemented!");
        return _response;
    }

    public void soundDialTone() {
        _response = "soundDialTone";
    }
    public void disconnectedLine() {
        _response = "disconnectedLine";
    }

    public void slowBusyTone() {
        _response = "slowBusyTone";
    }

    public void fastBusyTone() {
        _response = "fastBusyTone";
    }

    public void playMessage() {
        _response = "playMessage";
    }

    public void findConnection() {
        _response = "findConnection";
    }

    public void continues() {
        _response = "continues";
    }

    public void startTimer ()
    {
        _timer = new Timer();
        _timerTask = new TimerTask() {
            @Override
            public void run() {
                (_fsm.getState()).Exit(_fsm);
                _fsm.clearState();
                _fsm.setState (PhoneLineContext.PhoneLineFSM.Warning); //указывается состояние в
                                                                        // которое система переходит по таймауту (Warning)
                (_fsm.getState()).Entry(_fsm); }
        };
        _timer.schedule(_timerTask, 300);
//величина таймаута (1 такт = 100мс)
    }
    public void stopTimer()
    {
        _timerTask.cancel();
        _timerTask = null;
        _timer.cancel();
        _timer = null;
    }

}