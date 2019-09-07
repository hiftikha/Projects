package com.verkada.harooniftikhar.verkada.Adapter;

import android.content.Context;
import android.graphics.drawable.Drawable;
import android.os.AsyncTask;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import com.verkada.harooniftikhar.verkada.Fragments.VerkadaPresenter;
import com.verkada.harooniftikhar.verkada.R;

import java.net.URL;
import java.util.Date;
import java.util.List;

public class ResultsViewAdapter extends RecyclerView.Adapter<ResultsViewAdapter.CustomViewHolder> {

        private static final String TAG = VerkadaPresenter.class.getSimpleName();

        private List<List<Integer>> cells;
        private Context mContext;
        public ImageView mThumbnail;

        public ResultsViewAdapter(Context context, List<List<Integer>> selected) {
            this.cells = selected;
            this.mContext = context;
        }

        @Override
        public CustomViewHolder onCreateViewHolder(ViewGroup viewGroup, int i) {
            Log.i(TAG,"onCreateViewHolder");
            View view = LayoutInflater.from(viewGroup.getContext()).inflate(R.layout.table_row, null);
            CustomViewHolder viewHolder = new CustomViewHolder(view);
            return viewHolder;
        }

    @Override
        public void onBindViewHolder(CustomViewHolder customViewHolder, int i) {
        Log.i(TAG,"onBindViewHolder");

        Date date = new Date ();
        date.setTime((long)cells.get(i).get(0)*1000);

        String thumbnailFile = "";
            //Setting textviews
        try {
            customViewHolder.timestamp.setText(date.toString());
        } catch (Exception e) {
            e.printStackTrace();
        }

        customViewHolder.duration.setText("Duration: " + cells.get(i).get(1) + " (sec)");
        thumbnailFile = "http://ec2-54-187-236-58.us-west-2.compute.amazonaws.com:8021/ios/thumbnail/" + cells.get(i).get(0).toString() + ".jpg";
        Log.i(TAG,"thumbnail at: " + thumbnailFile);
        mThumbnail = customViewHolder.imageView;
        new HttpAsyncTask().execute(thumbnailFile);
        Log.i(TAG,"motionAt: " + cells.get(i).get(0) + " , " + cells.get(i).get(1));
        Log.i(TAG,"Cell #: " + i);
        }

    private class HttpAsyncTask extends AsyncTask<String, Void, Drawable> {
        @Override
        protected Drawable doInBackground(String... urls) {
            Drawable thumb = Drawable.createFromPath("");
            try {
                URL url = new URL(urls[0]);
                //InputStream is = (InputStream) new URL(thumbnailFile).getContent();
                 thumb = Drawable.createFromStream(url.openStream(), "src name");
            } catch (Exception e) {
                e.printStackTrace();
            }
            return thumb;
        }
        // onPostExecute displays the results of the AsyncTask.

        @Override
        protected void onPostExecute(Drawable result) {
            Log.e(TAG, "onGetImageExecute");
            Log.e(TAG, "Image Received: " + result);
            mThumbnail.setImageDrawable(result);

        }
    }

        @Override
        public int getItemCount() {
            Log.i(TAG,"getItemCount");
            Log.i(TAG,"item Count: " + cells.size());
            return (null != cells ? cells.size() : 0);
        }

        class CustomViewHolder extends RecyclerView.ViewHolder {
            protected ImageView imageView;
            protected TextView timestamp;
            protected TextView duration;

            public CustomViewHolder(View view) {
                super(view);
                this.imageView = view.findViewById(R.id.thumbnail);
                this.timestamp = view.findViewById(R.id.timestamp);
                this.duration = view.findViewById(R.id.duration);
            }
        }
}
