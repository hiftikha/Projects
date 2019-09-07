package com.verkada.harooniftikhar.verkada;

import com.verkada.harooniftikhar.verkada.Fragments.VerkadaPresenter;

import org.junit.Test;

import java.util.ArrayList;

import static org.junit.Assert.*;

public class VerkadaPresenterTest {

    @Test
    public void getStart() {
        long testStart = 987654;
        VerkadaPresenter testPresenter = new VerkadaPresenter();
        testPresenter.setStartT(testStart);

        assertEquals(testStart, testPresenter.getStart());
    }

    @Test
    public void getEnd() {
        long testEnd = 123456;
        VerkadaPresenter testPresenter = new VerkadaPresenter();
        testPresenter.setEndT(testEnd);

        assertEquals(testEnd, testPresenter.getEnd());
    }

    @Test
    public void getClicked() {
        Boolean[] testClicked = {true, false, true, false, true};
        VerkadaPresenter testPresenter = new VerkadaPresenter();
        testPresenter.setClicked(testClicked);

        assertTrue(testPresenter.getClicked(0));
        assertFalse(testPresenter.getClicked(1));
        assertEquals(testClicked,testPresenter.getClickedArray());
    }

    @Test
    public void getZones() {
        Cell one = new Cell(0,0);
        Cell two = new Cell(1,1);
        Cell three = new Cell(2,2);
        Cell four = new Cell(3,3);

        int[][] testMotion = new int[][] {{0,0},{1,1},{2,2},{3,3}};

        ArrayList<Cell> testZones = new ArrayList<>();
        testZones.add(one);
        testZones.add(two);
        testZones.add(three);
        testZones.add(four);

        VerkadaPresenter testPresenter = new VerkadaPresenter();
        testPresenter.setZones(testZones);

        assertEquals(testZones,testPresenter.getZones());
        assertEquals(testMotion,testPresenter.fillZones());
    }

    @Test
    public void getSecondsUTC() {
        long testUTC = 1000;
        VerkadaPresenter testPresenter = new VerkadaPresenter();
        testPresenter.getSecondsUTC(testUTC);

        assertEquals(1,testPresenter.getSecondsUTC(testUTC));
    }
}