package com.verkada.harooniftikhar.verkada.Interface;

import android.view.View;

import com.verkada.harooniftikhar.verkada.Cell;

import java.util.ArrayList;

public interface MainFragmentInteractionListener {

    interface Activity {

        void goToList(ArrayList<Cell> selected);

        void goToSearch();
    }

    interface Fragment {

    }
}
