package com.verkada.harooniftikhar.verkada;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.DefaultHttpClient;
import org.json.JSONObject;
import android.util.Log;

import org.json.JSONArray;
import org.json.JSONException;
import java.net.MalformedURLException;
import java.net.ProtocolException;
import java.util.ArrayList;
import java.util.List;


public class Server {

    private static final String TAG = Server.class.getSimpleName();
    private Motion VerkadaMotion;

    public Server(Motion motion){
        VerkadaMotion = motion;
    }

    public Motion getMotion(){
        return VerkadaMotion;
    }

    public String POST(String url, Motion motion){
        Log.e(TAG, "POST");
        InputStream inputStream = null;
        String result = "";
        try {

            // 1. create HttpClient
            HttpClient httpClient = new DefaultHttpClient();

            // 2. make POST request to the given URL
            HttpPost httpPost = new HttpPost(url);

            Log.i(TAG, "URL: " + url);
            String json = "";


            // 3. build jsonObject
            JSONObject jsonObject = new JSONObject();

            jsonObject.accumulate("motionZones", new JSONArray(motion.getZones()));
            jsonObject.accumulate("startTimeSec", motion.getStartTime());
            jsonObject.accumulate("endTimeSec", motion.getEndTime());

            // 4. convert JSONObject to JSON to String
            json = jsonObject.toString();
            Log.i(TAG, "JSON: " + json);

            // 5. set json to StringEntity
            StringEntity se = new StringEntity(json);

            // 6. set httpPost Entity
            httpPost.setEntity(se);

            // 7. Set some headers to inform server about the type of the content
            httpPost.setHeader("Accept", "json");
            httpPost.setHeader("Content-type", "application/json");

            // 8. Execute POST request to the given URL
            HttpResponse httpResponse = httpClient.execute(httpPost);

            // 9. receive response as inputStream
            inputStream = httpResponse.getEntity().getContent();
            //JsonArray motions =
            // 10. convert inputstream to string
            if(inputStream != null)

                //result = jo.get("motionAt").toString();
                result = readStream(inputStream);
            else
                result = "Did not work!";

        } catch (MalformedURLException e) {
            Log.e(TAG, "MalformedURLException: " + e.getMessage());
        } catch (ProtocolException e) {
            Log.e(TAG, "ProtocolException: " + e.getMessage());
        } catch (IOException e) {
            Log.e(TAG, "IOException: " + e.getMessage());
        } catch (Exception e) {
            Log.e(TAG, "Exception: " + e.getMessage());
        }

        // 11. return result
        return result;
    }

    private String readStream(InputStream is) throws IOException {
        Log.i(TAG, "readStream");
        StringBuilder sb = new StringBuilder();
        BufferedReader r = new BufferedReader(new InputStreamReader(is),1000);
        for (String line = r.readLine(); line != null; line =r.readLine()){
            sb.append(line);
            Log.i("GET json line:", line);
        }
        is.close();
        Log.i("GET json:", sb.toString());
        return sb.toString();
    }

    public List<List<Integer>> motionAtParser(JSONObject arr){
        JSONArray motionAt = new JSONArray();
        List<List<Integer>> motion = new ArrayList<>();

        try {
            motionAt = (JSONArray) arr.get("motionAt");
        } catch (JSONException e) {
            e.printStackTrace();
        }
        Log.e(TAG, "motionAt count: " + motionAt.length());

        for(int i= 0; i < motionAt.length(); i++){
            try {
                JSONArray tempJson = new JSONArray();
                tempJson = (JSONArray) motionAt.get(i);
                List<Integer> temp = new ArrayList<>();
                temp.add((Integer) tempJson.get(0));
                temp.add((Integer) tempJson.get(1));
                motion.add(temp);
                Log.e(TAG, "Motion: " + temp.get(0) + " , " + temp.get(1));
            } catch (JSONException e) {
                e.printStackTrace();
            }

        }
        return motion;
    }
}
