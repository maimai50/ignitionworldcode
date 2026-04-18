#include "main.h"
#include "configs.h"
#include "autons/autons.h"
#include "pros/misc.h"
#include "autonselector.h"	

LV_IMAGE_DECLARE(sixsevenn);  
void update_telemetry(lemlib::Chassis &chassis) {

    //battery thing
    int battery = pros::battery::get_capacity();
    char bat_buf[32];
    snprintf(bat_buf, sizeof(bat_buf), "Battery: %d%%", battery);
    lv_label_set_text(lbl_battery, bat_buf);

	//selected auton
    char auton_buf[64];
    if (selected_auton_id >= 0) {
        snprintf(auton_buf, sizeof(auton_buf), "Selected: %s", AUTON_NAMES[selected_auton_id]);
    } else {
        snprintf(auton_buf, sizeof(auton_buf), "Selected: None (Waiting)");
    }
    lv_label_set_text(lbl_status, auton_buf);

	//position things
    lemlib::Pose pose = chassis.getPose();
    char pos_buf[64];
    snprintf(pos_buf, sizeof(pos_buf), "X: %.1f  Y: %.1f  H: %.1f",
             pose.x, pose.y, pose.theta);
    lv_label_set_text(lbl_xyh, pos_buf);

 
    double l1 = pros::Motor(16).get_temperature();
    double l2 = pros::Motor(17).get_temperature();
    double l3 = pros::Motor(18).get_temperature();

    double r1 = pros::Motor(8).get_temperature();
    double r2 = pros::Motor(9).get_temperature();
    double r3 = pros::Motor(10).get_temperature();

	double i1  = pros::Motor(19).get_temperature(); //i = intake
	double i2  = pros::Motor(20).get_temperature();

	// F=C*9/5+32
    l1 = l1 * 9.0 / 5.0 + 32.0;
    l2 = l2 * 9.0 / 5.0 + 32.0;
    l3 = l3 * 9.0 / 5.0 + 32.0;

    r1 = r1 * 9.0 / 5.0 + 32.0;
    r2 = r2 * 9.0 / 5.0 + 32.0;
    r3 = r3 * 9.0 / 5.0 + 32.0;

	i1 = i1 * 9.0 / 5.0 + 32.0;
	i2 = i2 * 9.0 / 5.0 + 32.0;




    // Display
    char temp_buf[128];
    snprintf(temp_buf, sizeof(temp_buf),
        "L1: %.0f L2: %.0f L3: %.0f  R1: %.0f R2: %.0f R3 %.0f\nI1: %.0f I2: %.0f",
        l1, l2, l3,
        r1, r2, r3,
        i1, i2
    );

    lv_label_set_text(lbl_temps, temp_buf);
}

static void telemetry_timer_cb(lv_timer_t* timer) {
    update_telemetry(chassis);
}

void initialize() {
    chassis.calibrate();


    lv_obj_t* scr = lv_screen_active();

    lv_obj_t* img = lv_image_create(scr);
    
    lv_image_set_src(img, &sixsevenn); 
    lv_obj_center(img);

    pros::delay(2000);

    lv_obj_clean(scr);

    create_selector_ui();

    lv_timer_create(telemetry_timer_cb, 200, nullptr);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	switch(selected_auton_id) {
		case 0:
			threePlusFour();
			break;
		case 1:
			fourblockr();
			break;
		case 2:
			sevenblockr();
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
		 	break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		default:
			threePlusFour();
			break;
	}
}

void opcontrol() {
     while (true) {
		if (master.get_digital(DIGITAL_UP) && master.get_digital(DIGITAL_DOWN)) {
            autonomous();
        }
        pros::delay(25);
	}
}
