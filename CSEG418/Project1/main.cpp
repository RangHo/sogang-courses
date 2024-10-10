#include <array>
#include <limits>
#include <opencv2/opencv.hpp>

inline cv::Point2d rotate(const cv::Point2d point, double radian);

inline cv::Rect find_bounding_box(const cv::Size2d size, double radian);

inline cv::Vec3b interpolate(const cv::Mat img, const cv::Point2d point);

cv::Mat problem_a_rotate_forward(cv::Mat img, double angle)
{
    cv::Mat output;

    //////////////////////////////////////////////////////////////////////////////
    //                         START OF YOUR CODE                               //
    //////////////////////////////////////////////////////////////////////////////

    // Figure out the bounding box
    double angle_radian = -angle * CV_PI / 180.0;
    cv::Size2d img_size(img.rows, img.cols);
    cv::Rect bounding_box = find_bounding_box(img_size, angle_radian);

    // Initialize the output matrix with zeros
    output = cv::Mat::zeros(bounding_box.width, bounding_box.height, img.type());

    // Assign each pixel in the image to the output matrix
    for (int x = 0; x < img.rows; x++) {
        for (int y = 0; y < img.cols; y++) {
            auto rotated = rotate(cv::Point2d(x, y), angle_radian);
            output.at<cv::Vec3b>(rotated.x - bounding_box.x, rotated.y - bounding_box.y)
                = img.at<cv::Vec3b>(x, y);
        }
    }

    //////////////////////////////////////////////////////////////////////////////
    //                          END OF YOUR CODE                                //
    //////////////////////////////////////////////////////////////////////////////

    cv::imshow("a_output", output);
    cv::waitKey(0);
    return output;
}

cv::Mat problem_b_rotate_backward(cv::Mat img, double angle)
{
    cv::Mat output;

    //////////////////////////////////////////////////////////////////////////////
    //                         START OF YOUR CODE                               //
    //////////////////////////////////////////////////////////////////////////////

    // Figure out the bounding box
    double angle_radian = -angle * CV_PI / 180.0;
    cv::Size2d img_size(img.rows, img.cols);
    cv::Rect bounding_box = find_bounding_box(img_size, angle_radian);

    // Initialize the output matrix with zeros
    output = cv::Mat::zeros(bounding_box.width, bounding_box.height, img.type());

    // Assign each pixel in the image to the output matrix
    for (int x = 0; x < bounding_box.width; x++) {
        for (int y = 0; y < bounding_box.height; y++) {
            auto unrotated
                = rotate(cv::Point2d(x + bounding_box.x, y + bounding_box.y), -angle_radian);

            if (unrotated.x < 0 || unrotated.x >= img.rows || unrotated.y < 0
                || unrotated.y >= img.cols)
                continue;

            output.at<cv::Vec3b>(x, y) = img.at<cv::Vec3b>(unrotated.x, unrotated.y);
        }
    }

    //////////////////////////////////////////////////////////////////////////////
    //                          END OF YOUR CODE                                //
    //////////////////////////////////////////////////////////////////////////////

    cv::imshow("b_output", output);
    cv::waitKey(0);

    return output;
}

cv::Mat problem_c_rotate_backward_interarea(cv::Mat img, double angle)
{
    cv::Mat output;
    
    //////////////////////////////////////////////////////////////////////////////
    //                         START OF YOUR CODE                               //
    //////////////////////////////////////////////////////////////////////////////

    // Figure out the bounding box
    double angle_radian = -angle * CV_PI / 180.0;
    cv::Size2d img_size(img.rows, img.cols);
    cv::Rect bounding_box = find_bounding_box(img_size, angle_radian);

    // Initialize the output matrix with zeros
    output = cv::Mat::zeros(bounding_box.width, bounding_box.height, img.type());

    // Assign each pixel in the image to the output matrix
    for (int x = 0; x < bounding_box.width; x++) {
        for (int y = 0; y < bounding_box.height; y++) {
            auto unrotated
                = rotate(cv::Point2d(x + bounding_box.x, y + bounding_box.y), -angle_radian);

            if (unrotated.x < 0 || unrotated.x >= img.rows || unrotated.y < 0
                || unrotated.y >= img.cols)
                continue;

            output.at<cv::Vec3b>(x, y) = interpolate(img, unrotated);
        }
    }

    //////////////////////////////////////////////////////////////////////////////
    //                          END OF YOUR CODE                                //
    //////////////////////////////////////////////////////////////////////////////

    cv::imshow("c_output", output);
    cv::waitKey(0);

    return output;
}

cv::Mat Example_change_brightness(cv::Mat img, int num, int x, int y)
{
    /*
      img : input image
      num : number for brightness (increase or decrease)
      x : x coordinate of image (for square part)
      y : y coordinate of image (for square part)

     */
    cv::Mat output = img.clone();
    int size = 100;
    int height = (y + 100 > img.cols) ? img.cols : y + 100;
    int width = (x + 100 > img.rows) ? img.rows : x + 100;

    for (int i = x; i < width; i++) {
        for (int j = y; j < height; j++) {
            for (int c = 0; c < img.channels(); c++) {
                int t = img.at<cv::Vec3b>(i, j)[c] + num;
                output.at<cv::Vec3b>(i, j)[c] = t > 255 ? 255 : t < 0 ? 0 : t;
            }
        }
    }
    cv::imshow("output1", img);
    cv::imshow("output2", output);
    cv::waitKey(0);
    return output;
}

int main(void)
{
    double angle = -15.0f;

    cv::Mat input = cv::imread("./lena.jpg");
    // Fill problem_a_rotate_forward and show output
    problem_a_rotate_forward(input, angle);
    // Fill problem_b_rotate_backward and show output
    problem_b_rotate_backward(input, angle);
    // Fill problem_c_rotate_backward_interarea and show output
    problem_c_rotate_backward_interarea(input, angle);
    // Example how to access pixel value, change params if you want
    // Example_change_brightness(input, 100, 50, 125);
}


//////////////////////////////////////////////////////////////////////////////
//                            HELPER FUNCTIONS                              //
//////////////////////////////////////////////////////////////////////////////

inline cv::Point2d rotate(const cv::Point2d point, double radian)
{
    // Rotate the point
    double cos_theta = std::cos(radian);
    double sin_theta = std::sin(radian);
    int x = cos_theta * point.x - sin_theta * point.y;
    int y = sin_theta * point.x + cos_theta * point.y;
    return cv::Point(x, y);
}

inline cv::Rect find_bounding_box(const cv::Size2d size, double radian)
{
    // Calculate the size of the rotated image
    std::array<cv::Point2d, 4> points({ cv::Point2d(0.0, 0.0),
                                        cv::Point2d(0.0, size.height),
                                        cv::Point2d(size.width, 0.0),
                                        cv::Point2d(size.width, size.height) });

    int min_x = std::numeric_limits<int>::max();
    int min_y = std::numeric_limits<int>::max();
    int max_x = std::numeric_limits<int>::min();
    int max_y = std::numeric_limits<int>::min();

    for (auto point : points) {
        point = rotate(point, radian);

        if (point.x < min_x)
            min_x = point.x;
        if (point.y < min_y)
            min_y = point.y;
        if (point.x > max_x)
            max_x = point.x;
        if (point.y > max_y)
            max_y = point.y;
    }

    return cv::Rect(min_x, min_y, max_x - min_x, max_y - min_y);
}

inline cv::Vec3b interpolate(const cv::Mat img, const cv::Point2d point)
{
    // Consider the following structure:
    //     nw                   ne
    //       +-----------+-----+
    //       |           |     |
    //       |    point  |     |
    //       |         \ |     |
    //       +-----------0-----+
    //.      |           |     |
    //       +-----------+-----+
    //     sw                   se

    // Find the corner pixels
    cv::Vec3b nw = img.at<cv::Vec3b>(static_cast<int>(point.x), static_cast<int>(point.y));
    cv::Vec3b ne = img.at<cv::Vec3b>(static_cast<int>(point.x) + 1, static_cast<int>(point.y));
    cv::Vec3b sw = img.at<cv::Vec3b>(static_cast<int>(point.x), static_cast<int>(point.y) + 1);
    cv::Vec3b se = img.at<cv::Vec3b>(static_cast<int>(point.x) + 1, static_cast<int>(point.y) + 1);

    // Find the ratio of the point
    double dx = point.x - std::floor(point.x);
    double dy = point.y - std::floor(point.y);

    // Run bilinear interpolation
    return (nw * dx * dy) + (ne * (1 - dx) * dy) + (sw * dx * (1 - dy))
        + (se * (1 - dx) * (1 - dy));
}
