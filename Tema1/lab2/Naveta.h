#pragma once
#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"

class Naveta{

public:
	Circle2D *cerc_naveta;
	Polygon2D *poly_naveta, *burghiu;
	float directie = 0;
	float viteza = 3, viteza_aux = 0;
	bool burghiu_on = false;
	int chenar_x, chenar_y;
public:

	Naveta(float centru_x, float centru_y,int chenarx,int chenary){
		//adaug cercul
		cerc_naveta = new Circle2D(Point2D(centru_x, centru_y), 30, Color(255, 0, 0), false);

		//updatez detalii chenar
		chenar_x = chenarx;
		chenar_y = chenary;

		//adaug naveta
		poly_naveta = new Polygon2D(Color(255, 0, 0), false);
		poly_naveta->addPoint(Point2D(centru_x - 20, centru_y));
		poly_naveta->addPoint(Point2D(centru_x, centru_y + 25));
		poly_naveta->addPoint(Point2D(centru_x + 20, centru_y + 5));
		poly_naveta->addPoint(Point2D(centru_x, centru_y + 15));
		poly_naveta->addPoint(Point2D(centru_x - 10, centru_y));
		poly_naveta->addPoint(Point2D(centru_x, centru_y - 15));
		poly_naveta->addPoint(Point2D(centru_x + 20, centru_y - 5));
		poly_naveta->addPoint(Point2D(centru_x, centru_y - 25));

		//adaug burghiul
		burghiu = new Polygon2D(Color(255, 0, 0), true);
		burghiu->addPoint(Point2D(centru_x + 35, centru_y + 20));
		burghiu->addPoint(Point2D(centru_x + 90, centru_y));
		burghiu->addPoint(Point2D(centru_x + 35, centru_y - 20));
	}
	
	void translate_object_o(float x, float y, Object2D *ob){
		Transform2D::loadIdentityMatrix();
		Transform2D::translateMatrix(x, y);
		Transform2D::applyTransform_o(ob);
	}

	void translate(float x, float y){
		Transform2D::loadIdentityMatrix();
		Transform2D::translateMatrix(x, y);
		Transform2D::applyTransform_o(cerc_naveta);
		Transform2D::applyTransform_o(poly_naveta);
		Transform2D::applyTransform_o(burghiu);
	}

	void rotate(int param){
		float centru_x = 0, centru_y = 0;

		//if param 0 -> rotate_right
		//else -> rotate_left

		float unghi = 0.05;
		if (param != 0) unghi = -unghi;

		//updatam directia actuala a navei
		directie += unghi;

		//calcul centru poligon
		for (int i = 0; i < poly_naveta->points.size(); i++)
		{
			centru_x = centru_x + poly_naveta->transf_points[i]->x;
			centru_y = centru_y + poly_naveta->transf_points[i]->y;
		}
		centru_x = centru_x / 8;
		centru_y = centru_y / 8;

		//rotirea navei
		Transform2D::loadIdentityMatrix();
		Transform2D::translateMatrix(-centru_x, -centru_y);
		Transform2D::rotateMatrix(unghi);
		Transform2D::translateMatrix(centru_x, centru_y);
		Transform2D::applyTransform_o(poly_naveta);
		Transform2D::applyTransform_o(burghiu);

	}

	void move_straight(float viteza_aux){
		DrawingWindow::removeObject2D(poly_naveta);
		DrawingWindow::removeObject2D(cerc_naveta);

		//if (viteza_aux<viteza)
		//	viteza_aux += 0.05;

		translate(viteza_aux*cos(directie), viteza_aux*sin(directie));

		verifica_ecran();

		DrawingWindow::addObject2D(poly_naveta);
		DrawingWindow::addObject2D(cerc_naveta);
	}


	void verifica_ecran(){
		while (true){
			if ((cerc_naveta->transf_points[0]->x - 60) < 6){
				//mut inapoi unde era inainte de mutare
				translate(-viteza_aux*cos(directie), 0);
				//mut fix pe margine
				translate(-(cerc_naveta->transf_points[0]->x - 60 - 6), 0);
			}
			else
			if ((cerc_naveta->transf_points[0]->x) > chenar_x + 4){
				translate(-viteza_aux*cos(directie), 0);
				translate(chenar_x - cerc_naveta->transf_points[0]->x + 4, 0);
			}
			else
			if ((cerc_naveta->transf_points[0]->y - 30) < 6){
				translate(0, -viteza_aux*sin(directie));
				translate(0, -(cerc_naveta->transf_points[0]->y - 30 - 6));
			}
			else
			if ((cerc_naveta->transf_points[0]->y + 30) > chenar_y + 3){
				translate(0, -viteza_aux*sin(directie));
				translate(0, chenar_y - cerc_naveta->transf_points[0]->y - 30 + 3);
			}
			else break;
		}
	}
	void addNaveta2D(){
		DrawingWindow::addObject2D(poly_naveta);
		DrawingWindow::addObject2D(cerc_naveta);
	}
	void activateBurghiu(){
		DrawingWindow::addObject2D(burghiu);
	}
	void deactivateBurghiu(){
		DrawingWindow::removeObject2D(burghiu);
	}
};