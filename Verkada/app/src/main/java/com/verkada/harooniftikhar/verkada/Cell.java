package com.verkada.harooniftikhar.verkada;

import android.os.Parcel;
import android.os.Parcelable;

public class Cell implements Parcelable{

    private int x;
    private int y;

    public Cell(int xCor, int yCor){
        x = xCor;
        y = yCor;
    }

    public Cell(Parcel in){
        x = in.readInt();
        y = in.readInt();
    }

    public int[] getCell(){
        int[] cell = new int[2];
        cell[0] = x;
        cell[1] = y;
        return cell;
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeInt(x);
        dest.writeInt(y);
    }

    public static final Parcelable.Creator CREATOR =
            new Parcelable.Creator() {
                public Cell createFromParcel(Parcel in) {
                    return new Cell(in);
                }

                public Cell[] newArray(int size) {
                    return new Cell[size];
                }
            };
}
