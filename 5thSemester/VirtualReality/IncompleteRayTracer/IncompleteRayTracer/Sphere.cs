using System;
using System.Numerics;

namespace IncompleteRayTracer
{
    public class Sphere : Ellipsoid
    {
        private Vector Center { get; set; }
        private double Radius { get; set; }

        public Sphere(Vector center, double radius, Material material, Color color) : base(material: material, color:color)
        {
            Center = center;
            Radius = radius;
        }

        public Sphere(Vector center, double radius, Color color) : base(center, new Vector(1, 1, 1), radius, color)
        {
        }

        public override Intersection GetIntersection(Line line, double minDist, double maxDist)
        {
            var x0MinusC = line.X0 - GetCenter();
            var a = Vector.Dot(line.Dx, line.Dx);
            var b = 2 * Vector.Dot(x0MinusC, line.Dx);
            var c = Vector.Dot(x0MinusC, x0MinusC) - Math.Pow(Radius, 2);

            var discriminant = Math.Pow(b, 2) - 4 * a * c;

            if (discriminant < 0)
            {
                return new Intersection();
            }

            var t1 = (-b + Math.Sqrt(discriminant)) / (2 * a);
            var t2 = (-b - Math.Sqrt(discriminant)) / (2 * a);

            var tClosest = t1 < t2 ? t1 : t2;

            if (tClosest > minDist && tClosest < maxDist)
            {
                var point = line.CoordinateToPosition(tClosest);
                var normal = (point - GetCenter()) / Radius;
                return new Intersection(true, true, this, line, tClosest, point, normal);
            }

            return new Intersection();
        }

    }
}