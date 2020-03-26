import com.example.robogallery.roboImage

class RoboRepository (
) {
    private val roboGallery: MutableList<roboImage> = mutableListOf<roboImage>()

    fun addItem(roboImage: roboImage) {
        roboGallery.add(0, roboImage)
    }

    fun deleteItem(roboImage: roboImage) {
        roboGallery.removeAt(0)
    }
}