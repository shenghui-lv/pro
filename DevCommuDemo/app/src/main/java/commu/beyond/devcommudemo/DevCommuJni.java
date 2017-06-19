package commu.beyond.devcommudemo;

public class DevCommuJni {
    public static final int devInit = 66;
    public static final int devClose = 88;
    public static final int temperatureFlag = 1001;
    public static final int humidityFlag = 1002;
    public static final int co2Flag = 101;
    public static final int spiCH1 = 102;
    public static final int spiCH2 = 103;

    private DevCommuJni() {

    }

    private static class LazyHolder {
        private static final DevCommuJni INSTANCE = new DevCommuJni();
    }

    public static final DevCommuJni getInstance() {
        return LazyHolder.INSTANCE;
    }

    public native int SendCmdMessage(int cmd, byte[] inOutBuf, int dataLen, int inOutBufLen);

    static {
        System.loadLibrary("DevCommuJni");
    }
}
