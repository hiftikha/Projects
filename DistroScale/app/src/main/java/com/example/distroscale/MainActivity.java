package com.example.distroscale;

import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.design.widget.BottomNavigationView;
import android.support.v7.app.AppCompatActivity;
import android.view.MenuItem;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private TextView mTextMessage;


    private Episode first = new Episode("DistroTV Promo", "https:\\/\\/dstroscal1.s.llnwi.net\\/public\\/hls\\/promo\\/distrotv_sizzlereel_btreem_20190122\\/dtv_sizzlereel_thumb_center_600x800.jpg", "https:\\/\\/dstroscal1.s.llnwi.net\\/public\\/hls\\/22667\\/Short%20Content\\/Bollywood\\/Bollywood\\/12_04_2019\\/Alia_Bhatt_Varun_Dhawan_ENERGETIC_DANCE_On_Kalank_Songs_In_Jalandar_For_FANS.mp4");
    private Episode second = new Episode("FashionTV L'Original", "https:\\/\\/dstroscal1.s.llnwi.net\\/public\\/hls\\/ftv\\/ftv-vertical.jpg", "https:\\/\\/dstroscal1.s.llnwi.net\\/public\\/hls\\/22667\\/Short%20Content\\/Bollywood\\/Bollywood\\/12_04_2019\\/Tara_Sutaria_PRAISES_Alia_Bhatts_Singing_Student_Of_The_Year_2_Trailer_Launch_SOTY_2.mp4");
    private Episode third = new Episode("Outdoor, Adventure, Travel", "https:\\/\\/dstroscal1.s.llnwi.net\\/public\\/hls\\/22705\\/Adventure%2C+Travel+%26+Wellness\\/vertical2.jpg", "https:\\/\\/dstroscal1.s.llnwi.net\\/public\\/hls\\/22667\\/Short%20Content\\/Bollywood\\/Bollywood\\/12_04_2019\\/Tara_Sutaria_PRAISES_Alia_Bhatts_Singing_Student_Of_The_Year_2_Trailer_Launch_SOTY_2.mp4");


    private Season seasonOne = new Season("Best Season", new Episode[]{first,second,third});

    private MovieItem oneM = new MovieItem(1, "Salt Water", "https:\\/\\/dstroscal1.s.llnwi.net\\/public\\/hls\\/22703\\/saltwater\\/saltwater_v.jpg", "https:\\/\\/dstroscal1.s.llnwi.net\\/public\\/hls\\/22703\\/saltwater\\/31\\/qpemm.mp4");
    private MovieItem twoM = new MovieItem(2, "Insane Lousiana", "\"https:\\/\\/dstroscal1.s.llnwi.net\\/public\\/hls\\/22703\\/saltwater\\/31\\/p212w.3.jpg\"", "https:\\/\\/dstroscal1.s.llnwi.net\\/public\\/hls\\/22703\\/saltwater\\/31\\/p212w.mp4");
    private MovieItem threeM = new MovieItem(1,"Legally Blonde", "https:\\/\\/dstroscal1.s.llnwi.net\\/public\\/hls\\/22703\\/sportfishing\\/35\\/e3jpe.3.jpg", "https:\\/\\/dstroscal1.s.llnwi.net\\/public\\/hls\\/22703\\/saltwater\\/31\\/qpemm.mp4");
    private MovieItem fourM = new MovieItem(2, "Perfume", "imgurl", "vidurl");
    private MovieItem fiveM = new MovieItem(1,"The Machinist", "imgurl", "vidurl");

    private Channel channelOne = new Channel(1, "Top TV Series");
    private Channel channelTwo = new Channel(2, "Most Popular Movies");

    private Channel[] channelList = {channelOne,channelTwo};
    private MovieItem[] movieList = {oneM, twoM, threeM, fourM, fiveM};

    private DistroFeed myFeed = DistroFeed.getInstance();





    private BottomNavigationView.OnNavigationItemSelectedListener mOnNavigationItemSelectedListener
            = new BottomNavigationView.OnNavigationItemSelectedListener() {

        @Override
        public boolean onNavigationItemSelected(@NonNull MenuItem item) {
            switch (item.getItemId()) {
                case R.id.navigation_home:
                    mTextMessage.setText(R.string.live_tv);
                    return true;
                case R.id.navigation_dashboard:
                    mTextMessage.setText(R.string.free);
                    return true;
                case R.id.navigation_notifications:
                    mTextMessage.setText(R.string.my_distro);
                    return true;
            }
            return false;
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        myFeed.setChannels(channelList);
        myFeed.setMovies(movieList);

        mTextMessage = (TextView) findViewById(R.id.message);
        BottomNavigationView navigation = (BottomNavigationView) findViewById(R.id.navigation);
        navigation.setOnNavigationItemSelectedListener(mOnNavigationItemSelectedListener);
    }

}
