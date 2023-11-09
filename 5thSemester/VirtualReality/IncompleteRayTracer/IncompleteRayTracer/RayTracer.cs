using System;
using System.Runtime.InteropServices;

namespace IncompleteRayTracer
{
    class RayTracer
    {
        private Geometry[] geometries;
        private Light[] lights;

        public RayTracer(Geometry[] geometries, Light[] lights)
        {
            this.geometries = geometries;
            this.lights = lights;
        }

        private double ImageToViewPlane(int n, int imgSize, double viewPlaneSize)
        {
            return -n * viewPlaneSize / imgSize + viewPlaneSize / 2;
        }

        private Intersection FindFirstIntersection(Line ray, double minDist, double maxDist)
        {
            var intersection = new Intersection();

            foreach (var geometry in geometries)
            {
                var intr = geometry.GetIntersection(ray, minDist, maxDist);

                if (!intr.Valid || !intr.Visible) continue;

                if (!intersection.Valid || !intersection.Visible)
                {
                    intersection = intr;
                }
                else if (intr.T < intersection.T)
                {
                    intersection = intr;
                }
            }

            return intersection;
        }

        private bool IsLit(Vector point, Light light)
        {
            // TODO: ADD CODE HERE
            Vector lightDirection = (light.Position - point).Normalize();

            // Check for shadows
            foreach (var geometry in geometries)
            {
                // Ignore the geometry itself
                if (geometry is Light) continue;

                Intersection shadowIntersection =
                    geometry.GetIntersection(new Line(point, lightDirection), 0.001, double.MaxValue);

                // If there is an intersection between the point and the light, it is in shadow
                if (shadowIntersection.Valid && shadowIntersection.T < 1)
                {
                    return false; // Point is in shadow
                }
            }

            return true; // Point is lit by the light
        }

        public void Render(Camera camera, int width, int height, string filename)
        {
            var background = new Color(0.2, 0.2, 0.2, 1.0);
            var image = new Image(width, height);

            double aspectRatio = (double)width / height;
            double halfViewPlaneWidth = camera.ViewPlaneWidth / 2;
            double halfViewPlaneHeight = halfViewPlaneWidth / aspectRatio;

            for (var i = 0; i < width; i++)
            {
                for (var j = 0; j < height; j++)
                {
                    double x = ImageToViewPlane(i, width, camera.ViewPlaneWidth);
                    double y = ImageToViewPlane(j, height, camera.ViewPlaneHeight);

                    Vector viewPlanePoint = camera.Position + camera.Direction * camera.ViewPlaneDistance +
                                            camera.Up * x * halfViewPlaneWidth +
                                            camera.Up * y * halfViewPlaneHeight;

                    Line ray = new Line(camera.Position, viewPlanePoint);

                    Intersection intersection =
                        FindFirstIntersection(ray, camera.FrontPlaneDistance, camera.BackPlaneDistance);

                    if (intersection.Valid && intersection.Visible)
                    {
                        bool isLit = IsLit(intersection.Position, lights[0]); // Assuming there's only one light source

                        if (isLit)
                        {
                            // Calculate the color at the intersection point using the Lambertian reflection model
                            Vector lightDirection = (lights[0].Position - intersection.Position).Normalize();
                            double diffuseFactor = Math.Max(0, intersection.Normal * lightDirection);
                            Color pixelColor = intersection.Geometry.Material.Diffuse * diffuseFactor;

                            // Set the pixel color in the image
                            image.SetPixel(i, j, pixelColor);
                        }
                        else
                        {
                            // If the point is in shadow, use the background color
                            image.SetPixel(i, j, background);
                        }
                    }
                    else
                    {
                        // If there's no valid intersection, use the background color
                        image.SetPixel(i, j, background);
                    }
                }
            }

            // Store the rendered image
            image.Store(filename);
        }
    }
}