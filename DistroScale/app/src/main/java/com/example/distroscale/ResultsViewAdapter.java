package com.example.distroscale;

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

import java.net.URL;
import java.util.Date;
import java.util.List;

public class ResultsViewAdapter extends RecyclerView.Adapter<ResultsViewAdapter.CustomViewHolder> {

    private DistroFeed myFeed = DistroFeed.getInstance();

    public ResultsViewAdapter(Context context, List<List<Integer>> selected) {

    }

    @Override
    public CustomViewHolder onCreateViewHolder(ViewGroup viewGroup, int i) {

        View view = LayoutInflater.from(viewGroup.getContext()).inflate(R.layout.rv_child, null);
        CustomViewHolder viewHolder = new CustomViewHolder(view);
        return viewHolder;
    }

    @Override
    public void onBindViewHolder(CustomViewHolder customViewHolder, int i) {

    }

    class CustomViewHolder extends RecyclerView.ViewHolder {
        protected TextView title;
        protected TextView imgUrl;
        protected TextView movieUrl;

        public CustomViewHolder(View view) {
            super(view);
        }
    }
}
