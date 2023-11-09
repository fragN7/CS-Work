namespace VolumetricRayTracer
{
    public class Ellipsoid : Geometry
    {
        private Vector Center { get; }
        private Vector SemiAxesLength { get; }
        private double Radius { get; }

        public Vector GetCenter()
        {
            return this.Center;
        }
        
        
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
            var oc = line.X0 - Center;

            var a = line.Dx * line.Dx / (SemiAxesLength * SemiAxesLength);
            var b = oc * 2 * line.Dx / (SemiAxesLength * SemiAxesLength);
            var c = oc * oc / (SemiAxesLength * SemiAxesLength) - Radius * Radius;

            var discriminant = b * b - 4 * a * c;

            if (discriminant >= 0)
            {
                var sqrtDiscriminant = Math.Sqrt(discriminant);
                var t1 = (-b - sqrtDiscriminant) / (2 * a);
                var t2 = (-b + sqrtDiscriminant) / (2 * a);

                if ((t1 >= minDist && t1 <= maxDist) || (t2 >= minDist && t2 <= maxDist))
                {
                    var t = (t1 >= minDist && t1 <= maxDist) ? t1 : t2;
                    var intersectionPoint = line.CoordinateToPosition(t);
                    var normal = Normal(intersectionPoint);

                    return new Intersection(true, true, this, line, t, normal);
                }
            }

            return Intersection.NONE;
        }
        
        public Vector Normal(Vector point)
        {
            var n = point - Center;
            n.Normalize();
            return n;
        }
    }
    
}
