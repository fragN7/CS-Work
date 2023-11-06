using System;


namespace IncompleteRayTracer
{
    public class Ellipsoid : Geometry
    {
        private Vector Center { get; }
        private Vector SemiAxesLength { get; }
        private double Radius { get; }
        
        
        public Ellipsoid(Vector center, Vector semiAxesLength, double radius, Material material, Color color) : base(material, color)
        {
            Center = center;
            SemiAxesLength = semiAxesLength;
            Radius = radius;
        }

        public Ellipsoid(Vector center, Vector semiAxesLength, double radius, Color color) : base(color)
        {
            Center = center;
            SemiAxesLength = semiAxesLength;
            Radius = radius;
        }

        public override Intersection GetIntersection(Line line, double minDist, double maxDist)
        {
            var o = line.X0 - Center;
            var d = line.Dx;

            // Calculate the coefficients of the quadratic equation
            var a = d * d / (SemiAxesLength * SemiAxesLength);
            var b = 2 * (d * o) / (SemiAxesLength * SemiAxesLength);
            var c = o * o / (SemiAxesLength * SemiAxesLength) - Radius * Radius;

            // Calculate discriminant
            var discriminant = b * b - 4 * a * c;

            if (discriminant < 0)
            {
                return new Intersection();
            }
            else
            {
                // Calculate the two solutions of the quadratic equation
                var t1 = (-b - Math.Sqrt(discriminant)) / (2 * a);
                var t2 = (-b + Math.Sqrt(discriminant)) / (2 * a);

                if (t1 > minDist && t1 < maxDist)
                {
                    return new Intersection(true, true, this, line, t1);
                }
                else if (t2 > minDist && t2 < maxDist)
                {
                    return new Intersection(true, true, this, line, t2);
                }
                else
                {
                    return new Intersection();
                }
            }
        }
    }
}
