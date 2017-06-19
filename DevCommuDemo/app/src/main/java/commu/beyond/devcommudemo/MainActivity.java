package commu.beyond.devcommudemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.text.DecimalFormat;

public class MainActivity extends AppCompatActivity {

    public DevCommuJni devCommuJni;
    private Button co2Get, temperatureGet, humidityGet, pm25Get, tvocGet;
    private TextView co2Dis, temperatureDis, humidityDis, pm25Dis, tvocDis;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        co2Get = (Button) findViewById(R.id.CO2Get);
        temperatureGet = (Button) findViewById(R.id.temperatureGet);
        humidityGet = (Button) findViewById(R.id.humidityGet);
        pm25Get = (Button) findViewById(R.id.PM2_5Get);
        tvocGet = (Button) findViewById(R.id.TVOCGet);

        co2Get.setOnClickListener(mylistener);
        temperatureGet.setOnClickListener(mylistener);
        humidityGet.setOnClickListener(mylistener);
        pm25Get.setOnClickListener(mylistener);
        tvocGet.setOnClickListener(mylistener);

        co2Dis = (TextView) findViewById(R.id.textView1);
        temperatureDis = (TextView) findViewById(R.id.textView2);
        humidityDis = (TextView) findViewById(R.id.textView3);
        pm25Dis = (TextView) findViewById(R.id.textView4);
        tvocDis = (TextView) findViewById(R.id.textView5);

        devCommuJni = DevCommuJni.getInstance();
        devCommuJni.SendCmdMessage(DevCommuJni.devInit, null, 0, 0);
    }

    Button.OnClickListener mylistener = new Button.OnClickListener() {
        @Override
        public void onClick(View v) {
            int ret = 0;
            String toastStr = null;
            byte[] inOutBuf = new byte[1024];

            switch (v.getId()) {
                /*
                case R.id.CO2Get:   //获取CO2值
                    ret = devCommuJni.SendCmdMessage(DevCommuJni.co2Flag, inOutBuf, 2, inOutBuf.length);
                    if(ret >= 2) {
                        int co2value = (inOutBuf[0] << 8) + inOutBuf[1];
                        toastStr = "CO2 Value is : " + co2value;
                    } else {
                        toastStr = "Serial Data Read Fail";
                    }
                    co2Dis.setText(toastStr);
                    break;
*/
                case R.id.temperatureGet:   //获取温度值
                    DecimalFormat df = new DecimalFormat("######0.00");
                    ret = devCommuJni.SendCmdMessage(DevCommuJni.temperatureFlag, inOutBuf, 6, inOutBuf.length);
                    if (ret >= 6) {
                        int temp = (inOutBuf[0] * 256) + inOutBuf[1];
                        double cTemp = -45 + (175 * temp / 65535.0);
                        toastStr = "Temperature in Celsius:" + df.format(cTemp) + " C ";
                        temperatureDis.setText(toastStr);
                    } else {
                        toastStr = "Temperature Read Fail";
                    }
                    break;

                case R.id.humidityGet:   //获取湿度值
                    df = new DecimalFormat("######0.00");
                    ret = devCommuJni.SendCmdMessage(DevCommuJni.humidityFlag, inOutBuf, 6, inOutBuf.length);
                    if(ret >= 6) {
                        double humidity = 100 * (inOutBuf[3] * 256 + inOutBuf[4]) / 65535.0;

                        toastStr =" Relative Humidity:" + df.format(humidity) + " RH";
                        humidityDis.setText(toastStr);
                    } else {
                        toastStr = "Humidity Read Fail";
                    }
                    break;
                /*
                case R.id.PM2_5Get:
                    byte[] pm2_5Buf = new byte[] {(byte) 0xA3, 0x03};
                    System.arraycopy(pm2_5Buf, 0, inOutBuf, 0, pm2_5Buf.length);
                    //ret = devCommuJni.SendCmdMessage(DevCommuJni.PM2_5Flag, inOutBuf, pm2_5Buf.length, inOutBuf.length);
                    if (ret >= 0) {
                        toastStr = "SPI Send Success";
                    } else {
                        toastStr = "SPI Send Fail";
                    }*/
                default:
                    break;
            }
            if(null != toastStr) {
                Toast.makeText(getApplicationContext(), toastStr, Toast.LENGTH_SHORT).show();
            }
        }
    };

    @Override
    protected void onDestroy() {
        super.onDestroy();
        devCommuJni.SendCmdMessage(DevCommuJni.devClose, null, 0, 0);
    }

    public static int shortToBytes(short value, byte[] bytes, int offset) {
        int idx = offset;

        bytes[idx++] = (byte) (value & 0xFF);
        bytes[idx++] = (byte) ((value>>8) & 0xFF);

        return idx;
    }
}
