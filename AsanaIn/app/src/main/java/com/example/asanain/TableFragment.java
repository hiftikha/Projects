package com.example.asanain;

import android.content.Context;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

public class TableFragment extends Fragment {
    private static final String TAG = TableFragment.class.getSimpleName();

    private AsanaPresenter mPresenter;
    private RecyclerView mRecyclerView;
    private ResultsViewAdapter mAdapter;

    private MainFragmentInteractionListener.Activity mListener;

    public TableFragment(){

    }

    public void setPresenter(AsanaPresenter presenter){ mPresenter = presenter;}

    @Override
    public void onStart() {
        super.onStart();
    }

    @Override
    public void onResume() {
        super.onResume();
        //backButton.setOnClickListener(clickListener);

        Log.i(TAG, "setting presenter's onoverviewresume");
        mPresenter.onResume(this);
        Log.i(TAG, "succesfully set presenter's onoverviewresume");
    }

    @Override
    public void onPause() {
        super.onPause();
        //if( controllerView != null ) controllerView.setOnClickListener(null);

    }

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        Log.i(TAG, "onCreate");
        super.onCreate(savedInstanceState);
        mPresenter = new AsanaPresenter(getContext());
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        Log.i(TAG, "about to inflate view");
        View view = inflater.inflate(R.layout.fragment_table, container, false);

        mRecyclerView = view.findViewById(R.id.Asana_recycler);
        Log.i(TAG,"zones selected about to be passed to recyclerView: " + mPresenter.getZones().size());
        mAdapter = new ResultsViewAdapter(getContext(), mPresenter.getMotionAt());
        mRecyclerView.setAdapter(mAdapter);
        Log.i(TAG, "done inflating view");
        return view;
    }

    @Override
    public void onAttach(Context context) {
        super.onAttach(context);
        if (context instanceof MainFragmentInteractionListener.Activity) {
            mListener = (MainFragmentInteractionListener.Activity) context;
        } else {
            throw new RuntimeException(context.toString()
                    + " must implement OnFragmentInteractionListener");
        }
    }

    @Override
    public void onDestroyView() {
        Log.i(TAG, "onDestroyView");
        super.onDestroyView();
        mPresenter.onDestroyView();
        // These no longer exist:
    }

    @Override
    public void onDetach() {
        super.onDetach();
        mListener = null;
    }

}
