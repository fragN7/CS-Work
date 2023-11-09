namespace VolumetricRayTracer
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
            var intersection = Intersection.NONE;

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
            var ray = new Line(light.Position, point);
            var intersection = FindFirstIntersection(ray, 0.0, (light.Position - point).Length());
            
            return intersection.Valid;
        }

        public void Render(Camera camera, int width, int height, string filename)
        {
            var background = new Color(0.2, 0.2, 0.2, 1.0);

            var image = new Image(width, height);

            for (var i = 0; i < width; i++)
            {
                for (var j = 0; j < height; j++)
                {
                    // TODO: ADD CODE HERE
                    var x0 = camera.Position;
                    var x1 = camera.Position +
                             camera.Direction * camera.ViewPlaneDistance +
                             (camera.Up ^ camera.Direction) * ImageToViewPlane(i, width, camera.ViewPlaneWidth) +
                             camera.Up * ImageToViewPlane(j, height, camera.ViewPlaneHeight);

                    var intersection = FindFirstIntersection(new Line(x0, x1), camera.FrontPlaneDistance,
                        camera.BackPlaneDistance);

                    if (intersection.Geometry == null)
                    {
                        image.SetPixel(i, j, new Color());
                    }
                    else
                    {
                        var color = new Color();
                        var material = intersection.Geometry.Material;

                        foreach (var light in lights)
                        {
                            var lightColor = material.Ambient * light.Ambient;

                            if (IsLit(intersection.Position, light))
                            {
                                var n = (intersection.Position - ((Sphere)intersection.Geometry).GetCenter()).Normalize();
                                var t = (light.Position - intersection.Position).Normalize();

                                if (n * t > 0)
                                {
                                    lightColor += material.Diffuse * light.Diffuse * (n * t);
                                }

                                var e = (camera.Position - intersection.Position).Normalize();
                                var r = n * (n * t) * 2 - t;

                                if (e * r > 0)
                                {
                                    lightColor += material.Specular * light.Specular *
                                                  Math.Pow((e * r), material.Shininess);
                                }

                                lightColor *= light.Intensity;
                            }

                            color += lightColor;
                        }

                        image.SetPixel(i, j, background);
                    }
                }

                image.Store(filename);
            }
        }
    }
}