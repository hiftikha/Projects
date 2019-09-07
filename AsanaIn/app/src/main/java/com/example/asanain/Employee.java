package com.example.asanain;

import android.media.Image;
import android.os.Parcel;
import android.os.Parcelable;

import javax.annotation.Nullable;

public class Employee implements Parcelable {

    private String first;
    private String last;
    private String name;
    private String headline;
    private Boolean hasPic;
    private String profile = "";

    public Employee(String f, String l, String n, String h, Boolean p, String pic){
        first = f;
        last = l;
        name = n;
        headline = h;
        hasPic = p;
        profile = pic;
    }

    public Employee(Parcel in){
        first = in.readString();
        last = in.readString();
        headline = in.readString();
    }

    public String getName(){

        return name;
    }

    public String getHeadline(){

        return headline;
    }

    public String getPic(){

        return profile;
    }

    public Boolean getHasPic(){
        return hasPic;
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeString(first);
        dest.writeString(last);
        dest.writeString(headline);
    }

    public static final Parcelable.Creator CREATOR =
            new Parcelable.Creator() {
                public Employee createFromParcel(Parcel in) {
                    return new Employee(in);
                }

                public Employee[] newArray(int size) {
                    return new Employee[size];
                }
            };
}
